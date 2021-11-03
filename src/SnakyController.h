#ifndef H_SNAKY_CONTROLLER
#define H_SNAKY_CONTROLLER



#include "Snaky.h"
#include "engine/handle/Timer.h"
#include "engine/handle/MouseListener.h"
#include "engine/handle/Mouse.h"
#include "engine/render/Window.h"
#include "src/Field.h"



class SnakyController : public Timer, public MouseListener
{

public:
    SnakyController(Snaky *puppet, Camera *camera, Field *field);
    
    void onTick() override; 
    
    void onMouseLeftClick() override; 
    
private:
    Snaky *m_puppet;
    Camera *m_camera;
    Field *m_field;
};



#endif // H_SNAKY_CONTROLLER
