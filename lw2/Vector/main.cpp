#include "Vector.h"

int main()
{
    try
    {
        std::vector<double> vector(std::istream_iterator<double>{std::cin}, std::istream_iterator<double>{});
        MultiplieVectorByMunimum(vector);
        std::ranges::sort(vector);
        WriteVector(vector, std::cout);
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}