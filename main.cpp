#include <iostream>

#include "src/Initializer.h"



int main()
{
    std::cout << "HELLOOOOOOOOOO WORLD!!!!" << std::endl;
    
    
    
    Initializer::init()->startGameCycle();
    
    
    
    std::cout << "borks!" << std::endl;
    return 0;
}
