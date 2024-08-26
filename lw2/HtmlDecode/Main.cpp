#include "HtmlDecode.h"

int main()
{
    try
    {
        std::string decodedString;
        while (std::getline(std::cin, decodedString))
        {
            std::cout << HtmlDecode(decodedString) << std::endl;
        }
    }
    catch (std::exception const& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
