#ifndef H_LOG
#define H_LOG



// this class saves, stores, and outputs all debugging information



#include <string>
#include <iostream>
#include <fstream>

#include <list>



class Log
{

public:
    static Log * inst();
    
    void message(std::string msg);
    void warning(std::string wrn);
    void error(std::string err);
    
    void printLog(int numberOfMsgs);
    void saveLog(int numberOfMsgs);
    
private:
    static Log *m_instance;
    static std::list<std::string> m_messages;
};



#endif // H_LOG
