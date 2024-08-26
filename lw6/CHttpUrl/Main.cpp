#include "CHttpUrl.h"
#include <iostream>

int main()
{
    std::string url;
    std::cout << "> ";
    while (std::getline(std::cin, url))
    {
        try
        {
            CHttpUrl httpUrl(url);
            std::cout << httpUrl.GetURL() << std::endl;
        }
        catch (CUrlParsingError const& e)
        {
            std::cout << "Parse error: " << e.what() << std::endl;
        }
        catch (std::exception const& e)
        {
            std::cout << "Unexpected error: " << e.what() << std::endl;
        }
        std::cout << "> ";
    }
    return EXIT_SUCCESS;
}