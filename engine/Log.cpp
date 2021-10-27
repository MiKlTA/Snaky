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
    inst()->m_messages.push_back(msg);
}

void Log::warning(std::string wrn)
{
    inst()->m_messages.push_back(wrn);
}

void Log::error(std::string err)
{
    inst()->m_messages.push_back(err);
}



void Log::printLog(int numberOfMsgs)
{
    // TODO: print to the console
}

void Log::saveLog(int numberOfMsgs)
{
    // TODO: save to file
}
