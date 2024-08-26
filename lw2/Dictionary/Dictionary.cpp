#include "Dictionary.h"

std::vector<std::string> HyphenateByTheFirstSpace(std::string const& line)
{
	char separator = ' ';
	std::vector<std::string> result;
	size_t wordEndPos = line.find_first_of(separator);
	if (wordEndPos != std::string::npos)
	{
		auto firstPart = line.substr(0, wordEndPos);
		std::transform(firstPart.begin(), firstPart.end(), firstPart.begin(),
			[](unsigned char c) { return std::tolower(c); });
		result.push_back(firstPart);

		size_t translateStartPos = line.find_first_not_of(separator, wordEndPos + 1);
		if (translateStartPos != std::string::npos)
		{
			auto secondPart = line.substr(translateStartPos);
			result.push_back(secondPart);
		}
	}

	return result;
}

std::map<std::string, std::string> GetDictionary(std::string const& dictionaryFilePath)
{	
	std::ifstream dictionaryFile(dictionaryFilePath);
	if (!dictionaryFile.is_open())
	{
		return {};
	}

	std::map<std::string, std::string> dictionary;
	std::string collation;
	while (std::getline(dictionaryFile, collation))
	{
		if (collation.empty())
		{
			continue;
		}

		auto collationVector = HyphenateByTheFirstSpace(collation);
		if (collationVector.empty())
		{
			throw std::invalid_argument("Неправильно задан словарь. Попробуйте другой файл.");
		}

		dictionary[collationVector[0]] = collationVector[1];
	}

	return dictionary;
}

std::string Translate(std::string & word, std::map<std::string, std::string> & dictionary)
{
	std::transform(word.begin(), word.end(), word.begin(),
		[](unsigned char c) { return std::tolower(c); });
	std::string translate = dictionary[word];

	return translate;
}

void SaveDictionary(std::string const& filePath, std::map<std::string, std::string> const& dictionary)
{
	// разобраться в std::ofstream::trunc
	std::ofstream dictionaryFile(filePath, std::ofstream::out | std::ofstream::trunc);

	if (!dictionaryFile.is_open())
	{
		throw std::invalid_argument("Файл не найден. Попробуйте другой путь.");
	}

	for (auto &[word, translate] : dictionary)
	{
		if (!(dictionaryFile << word << " " << translate << std::endl))
		{
			throw std::overflow_error("Не удалось сохранить словарь.");
		}
	}

	std::cout << "Словарь успешно сохранен." << std::endl;
}
