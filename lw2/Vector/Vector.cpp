#include "Vector.h"

void MultiplieVectorByMunimum(std::vector<double>& vector)
{
    if (vector.empty())
    {
        return;
    }

    double min = *std::min_element(vector.begin(), vector.end());
    std::transform(vector.begin(), vector.end(), vector.begin(), [min](double number) { return number * min; });
}

void WriteVector(std::vector<double> const& vector, std::ostream& outputFile)
{
    int precision = 3;

    outputFile << std::setprecision(precision) << std::fixed;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<double>(outputFile, " "));

    if (!(outputFile << '\n'))
    {
        throw std::runtime_error("Failed to write data to file");
    }

    if (!(outputFile.flush()))
    {
        throw std::runtime_error("Failed to save data to file");
    }
}