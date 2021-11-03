#ifndef H_SNAKY_CONTROLLER
#define H_SNAKY_CONTROLLER



#include "Snaky.h"
#include "engine/handle/Timer.h"
#include "engine/handle/MouseListener.h"



class SnakyController : public Timer, public MouseListener
{

public:
    SnakyController(Snaky *puppet);
    
    void onTick() override; 
    
    void onMouseLeftClick() override {}; 
    
private:
    Snaky *m_puppet;
};



#endif // H_SNAKY_CONTROLLER
