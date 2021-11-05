#ifndef H_SNAKY_CONTROLLER
#define H_SNAKY_CONTROLLER



#include "Snaky.h"
#include "engine/handle/Timer.h"
#include "engine/handle/MouseListener.h"
#include "engine/handle/Mouse.h"
#include "engine/render/Window.h"
#include "src/Field.h"
#include "src/FoodCreator.h"



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
    FoodCreator *m_foodCreator;
};



#endif // H_SNAKY_CONTROLLER
