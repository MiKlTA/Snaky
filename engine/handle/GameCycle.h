#ifndef H_GAME_CYCLE
#define H_GAME_CYCLE



#include <vector>
#include <algorithm>


class Timer;



class GameCycle
{

public:
    static GameCycle * inst();
    
    void addTimer(Timer *timer);
    void remTimer(Timer *timer);
    
	void update(double curTime);
    
private:
    static GameCycle *m_instance;
    
    std::vector<Timer *> m_timers;
};



#endif // H_GAME_CYCLE
