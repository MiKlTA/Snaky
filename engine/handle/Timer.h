#ifndef H_TIMER
#define H_TIMER



class Timer
{
    
public:
    Timer(double delay);
    virtual ~Timer();
    
    double getDelay() const {return m_delay;};
    void checkTime(double curTime);
    virtual void onTick(double curTime) = 0;
    
    void pause() {m_paused = true;};
    void resume() {m_paused = false;};
    
private:
    const double m_delay;
    double m_lastUpdTime;
    bool m_paused;
};



#endif // H_TIMER
