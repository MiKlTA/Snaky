#ifndef H_SNAKY_CONTROLLER
#define H_SNAKY_CONTROLLER



#include "Snaky.h"
#include "SnakyCreator.h"
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
    
    void onTick(double curTime) override; 
    
    void onMouseMove(double x, double y) override;
    
    static float initialCameraSize() {return 3.0f;};
    static float maxCameraSize() {return 15.0f;};
    
private:
    Snaky *m_puppet;
    Camera *m_camera;
    Field *m_field;
    FoodCreator *m_foodCreator;
};



#endif // H_SNAKY_CONTROLLER
