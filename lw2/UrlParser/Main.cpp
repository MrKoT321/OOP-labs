#include "UrlParser.h"

#include <string>

namespace
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
}

void PrintErrorMessage(std::ostream& otput)
{
	otput << "Url can not being parsed. Try another." << std::endl;
}

int main()
{
	std::string url;
	while (std::getline(std::cin, url)) 
	{
		try
		{
			if (ParseURL(url, protocol, port, host, document))
			{
				std::cout << "HOST: " << host << std::endl;
				std::cout << "PORT: " << port << std::endl;
				std::cout << "DOC: " << document << std::endl;
			}
			else
			{
				PrintErrorMessage(std::cout);
			}
		}
		catch (std::exception const& e)
		{
			PrintErrorMessage(std::cout);
		}
	}
}