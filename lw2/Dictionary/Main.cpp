#include "Dictionary.h"

// �������������� ��������� �� ���������
// ������� ������� main
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (argc != 2)
	{
		std::cout << "������� �������. ����������: dictionary.exe <dictionary_path>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string dictionaryFilePath = argv[1];

	try
	{
		auto dictionary = GetDictionary(dictionaryFilePath);
		auto pastDictionary = dictionary;
		std::string wordToTranslate;
		bool shouldSave = false;
		bool shouldChangeDictionary = false;


		while (true)
		{
			std::string word;
			std::cout << ">";
			std::getline(std::cin, word);

			if (shouldChangeDictionary)
			{
				shouldChangeDictionary = false;
				if (word.empty())
				{
					continue;
				}

				dictionary[wordToTranslate] = word;
				continue;
			}

			if (shouldSave)
			{
				if (word == "Y" || word == "y")
				{
					SaveDictionary(dictionaryFilePath, dictionary);
				}
				break;
			}

			if (word == "...")
			{
				if (dictionary != pastDictionary)
				{
					shouldSave = true;
					std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
					continue;
				}
				std::cout << "������� �� ��� �������. ��������� ���������." << std::endl;
				break;
			}

			auto translate = Translate(word, dictionary);
			if (!translate.empty())
			{
				std::cout << translate << std::endl;
			}
			else
			{
				std::cout << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������." << std::endl;
				wordToTranslate = word;
				shouldChangeDictionary = true;
			}
		}
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}