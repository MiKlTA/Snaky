#ifndef H_CONSOLE
#define H_CONSOLE



// This class is responsible for the input/output of information to the console



#include <iostream>
#include <string>



class Console
{

public:
    static void print(std::string text);
    
    static char readChar();
    static int readNumber();
    static std::string readString();
};




#endif // H_CONSOLE
