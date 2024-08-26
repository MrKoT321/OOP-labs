#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <format>

struct Arguments
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replacementString;
};

std::optional<Arguments> InitArguments(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return std::nullopt;
	}

	Arguments args;

	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replacementString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	std::string result;
	size_t pos = 0;
	size_t lastPos = 0;
	size_t searchLength = searchString.size();

	while (pos != std::string::npos)
	{
		pos = subject.find(searchString, pos);
		result.append(subject, lastPos, pos - lastPos);
		if (pos != std::string::npos)
		{
			result.append(replacementString);
			pos += searchLength;
			lastPos = pos;
		}
	}

	return result;
}

bool CopyStreamWithReplacement(std::ifstream& inputFile, std::ofstream& outputFile,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		if (!(outputFile << ReplaceString(line, searchString, replacementString) << "\n"))
		{
			std::cout << "Failed to write data to file\n";
			return false;
		}
	}

	if (!inputFile.eof())
	{
		std::cout << "Failed to read data from file\n";
		return false;
	}
	
	return true;
}

bool CopyFileWithReplacement(std::optional<Arguments> args)
{
	std::ifstream inputFile(args->inputFileName);
	std::ofstream outputFile(args->outputFileName);

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		std::cout << "Failed to open files\n" << "Please, check file names\n";
		return false;
	}

	if (!CopyStreamWithReplacement(inputFile, outputFile, args->searchString, args->replacementString))
	{
		return false;
	}

	if (!outputFile.flush())
	{
		std::cout << "Failed to upload data to file\n";
		return false;
	}

	return true;
}

// Функции с полезной работой не должны ничего

int main(int argc, char* argv[])
{
	bool hasError = false;
	auto args = InitArguments(argc, argv);

	if (!(args != std::nullopt))
	{
		return 1;
	}

	if (!CopyFileWithReplacement(args))
	{
		return 1;
	}

	return 0;
}