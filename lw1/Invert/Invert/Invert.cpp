#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <optional>
#include <iomanip>

using Matrix3x3 = std::array<std::array<double, 3>, 3>;

struct Arguments
{
	std::string inputFileName;
};

std::optional<Arguments> InitArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: invert.exe <matrix file1>\n";
		return std::nullopt;
	}

	Arguments args;
	args.inputFileName = argv[1];

	return args;
}

Matrix3x3 ReadMatrix(std::string const& inputFileName)
{
	std::ifstream inputfile(inputFileName);
	if (!inputfile.is_open())
	{
		throw std::invalid_argument("Failed to open file for reading");
	}

	Matrix3x3 matrix;
	int mmatrixSize = 3;

	for (int i = 0; i < mmatrixSize; i++)
	{
		for (int j = 0; j < mmatrixSize; j++)
		{
			if (!(inputfile >> matrix[i][j]))
			{
				throw std::runtime_error("Error while reading input file");
			}
		}
	}
	
	return matrix;
}

void WriteMatrix(Matrix3x3 const& matrix, std::ostream& outputFile)
{
	int precision = 3;
	double epsilon = 1e-3;
	int matrixSize = 3;

	outputFile << std::setprecision(precision) << std::fixed;
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			double element = abs(matrix[i][j]) < epsilon ? 0 : matrix[i][j];
			if (!(outputFile << element << " "))
			{
				throw std::runtime_error("Failed to upload data to file");
			}
		}
		if (!(outputFile << '\n'))
		{
			throw std::runtime_error("Failed to upload data to file");
		}
	}

	if (!(outputFile.flush()))
	{
		throw std::runtime_error("Failed to save data to file");
	}
}

Matrix3x3 GetTransponsedMatrix(Matrix3x3 const& matrix)
{
	Matrix3x3 transponsedMatrix = matrix;
	int matrixSize = 3;

	for (int i = 1; i < matrixSize; i++)
	{
		for (int j = 0; j < i; j++)
		{
			std::swap(transponsedMatrix[i][j], transponsedMatrix[j][i]);
		}
	}
	
	return transponsedMatrix;
}

double GetMinorDeterminant(Matrix3x3 const& matrix, int i, int j)
{
	int matrixSize = 3;
	int i1 = (matrixSize + i - 1) % matrixSize;
	int i2 = (matrixSize + i + 1) % matrixSize;
	if (i1 > i2)
	{
		std::swap(i1, i2);
	}
	int j1 = (matrixSize + j - 1) % matrixSize;
	int j2 = (matrixSize + j + 1) % matrixSize;
	if (j1 > j2)
	{
		std::swap(j1, j2);
	}

	return matrix[i1][j1] * matrix[i2][j2] - matrix[i1][j2] * matrix[i2][j1];
}

double GetDeterminant(Matrix3x3 const& matrix)
{
	double algebraicAddition1 = matrix[0][0] * GetMinorDeterminant(matrix, 0, 0);
	double algebraicAddition2 = matrix[1][0] * GetMinorDeterminant(matrix, 1, 0);
	double algebraicAddition3 = matrix[2][0] * GetMinorDeterminant(matrix, 2, 0);

	return algebraicAddition1 - algebraicAddition2 + algebraicAddition3;
}

// можно заменить на std::optional
Matrix3x3 InvertMatrix(Matrix3x3 const& matrix)
{
	auto determinant = GetDeterminant(matrix);
	
	if (determinant == 0)
	{
		throw std::invalid_argument("Matrix determinant equal to 0. There is no inverse matrix.");
	}

	Matrix3x3 inversiveMatrix;
	Matrix3x3 transponsedMatrix = GetTransponsedMatrix(matrix);
	int matrixSize = 3;

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			auto multiplier = (i + j) % 2 ? -1 : 1;
			auto minorDeterminant = GetMinorDeterminant(transponsedMatrix, i, j);
			inversiveMatrix[i][j] = multiplier * minorDeterminant / determinant;
		}
	}
	
	return inversiveMatrix;
}

int main(int argc, char* argv[])
{
	auto args = InitArguments(argc, argv);

	if (!args.has_value())
	{
		return 1;
	}

	try
	{
		auto matrix = ReadMatrix(args->inputFileName);
		auto inversiveMatrix = InvertMatrix(matrix);
		WriteMatrix(inversiveMatrix, std::cout);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what() << '\n';
		return 1;
	}

	return 0;
}