#ifndef H_TIMER
#define H_TIMER



class Timer
{
    
public:
    Timer(double delay);
    virtual ~Timer();
    
    double getDelay() const {return m_delay;};
    void checkTime(double curTime);
    virtual void onTick() = 0;
    
private:
    const double m_delay;
    double m_lastUpdTime;
};



#endif // H_TIMER
