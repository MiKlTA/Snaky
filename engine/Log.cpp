#include "Log.h"



Log *Log::m_instance = nullptr;
std::list<std::string> Log::m_messages = std::list<std::string>();



Log * Log::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new Log;
    }
    return m_instance;
}



void Log::message(std::string msg)
{
    inst()->m_messages.push_back("|MSG:| " + msg + "|:MSG|");
}

void Log::warning(std::string wrn)
{
    inst()->m_messages.push_back("|WRN:| " + wrn + "|:WRN|");
}

void Log::error(std::string err)
{
    inst()->m_messages.push_back("|ERR:| " + err + "|:ERR|");
}



void Log::printLog(int numberOfMsgs)
{
    long msgsCount = m_messages.size();
    for (
         int i = 0;
         (i < numberOfMsgs || numberOfMsgs == -1) && i < msgsCount;
         ++i
         )
    {
        std::cout << m_messages.front() << std::endl;
        m_messages.pop_front();
    }
}

void Log::saveLog(int numberOfMsgs)
{
    // TODO: save to file
}
