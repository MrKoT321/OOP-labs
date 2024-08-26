#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include <locale.h>
#include <Windows.h>

// ввести синоним типа std::map<...>
// убрать лишние include, только те, что нужны дл€ компил€ции
std::map<std::string, std::string> GetDictionary(std::string const& dictionaryFilePath);

std::string Translate(std::string & word, std::map<std::string, std::string> & dictionary);

void SaveDictionary(std::string const& filePath, std::map<std::string, std::string> const& dictionary);
