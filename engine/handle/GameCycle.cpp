#include "GameCycle.h"

#include "Timer.h"



GameCycle *GameCycle::m_instance = nullptr;



GameCycle * GameCycle::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new GameCycle;
    }
    return m_instance;
}



void GameCycle::addTimer(Timer *timer)
{
    m_timers.push_back(timer);
}

void GameCycle::remTimer(Timer *timer)
{
    auto found = std::find(m_timers.begin(), m_timers.end(), timer);
    if (found != m_timers.end())
    {
        m_timers.erase(found);
    }
}



void GameCycle::update(double curTime)
{
    for (auto t : m_timers)
    {
        t->checkTime(curTime);
    }
}
