#include <iostream>
#include <string>
#include <cstdint>

bool IsMagicNumber(uint64_t number) 
{
    return false;
}

int main() {
    uint64_t inputNumber;
    
    if (!(std::cin >> inputNumber))
    {
        std::cout << "Error \n";
        return 0;
    }
    
    if (IsMagicNumber(inputNumber)) 
    {
        std::cout << "Magic\n";
    }
    else 
    {
        std::cout << "Non-magic\n";
    }

    return 0;
}