#ifndef H_SNAKY_CONTROLLER
#define H_SNAKY_CONTROLLER



#include "Snaky.h"
#include "engine/handle/Timer.h"



class SnakyController : public Timer
{

public:
    SnakyController(Snaky *puppet);
    
    void onTick() override; 
    
private:
    Snaky *m_puppet;
};



#endif // H_SNAKY_CONTROLLER
