#include <iostream>

#include <system/isystem.hpp>

int main()
{
    std::cout << "MAIN" << std::endl;

    __N_SYSTEM__::createSystem()->run();
    
    return 0;
}
