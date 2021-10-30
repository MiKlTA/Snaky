#include "Timer.h"

#include "GameCycle.h"



Timer::Timer(double delay)
    : m_delay(delay),
      m_lastUpdTime(0.0)
{
    GameCycle::inst()->addTimer(this);
}

Timer::~Timer()
{
    GameCycle::inst()->remTimer(this);
}



void Timer::checkTime(double curTime)
{
    if (curTime - m_lastUpdTime > m_delay)
    {
        m_lastUpdTime = curTime;
        onTick();
    }
}
