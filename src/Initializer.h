#ifndef H_INITIALIZER
#define H_INITIALIZER



#include <iostream>
#include <random>
#include <ctime>



#include "engine/gl.h"
#include "src/Rectangle.h"
#include "src/Field.h"
#include "src/Snaky.h"
#include "src/SnakyCreator.h"
#include "src/SnakyController.h"
#include "src/FoodCreator.h"
#include "engine/handle/GameCycle.h"
#include "engine/render/Window.h"
#include "engine/Log.h"



class Initializer
{
public:
    static Initializer *init();
    
    void startGameCycle();
    
private:
    Initializer();
    static Initializer *m_instance;
    
    Window *m_window;
    Render *m_render;
    Camera *m_camera;
    
    Field *m_field;
    FoodCreator *m_foodCreator;
    SnakyCreator *m_snakyCreator;
    
    
    
    void _init();
    
    static glm::ivec2 fieldSize() {return glm::ivec2(10, 10);};
    static int normalFoodCount() {return 5;};
    static int maximumFoodCount() {return 15;};
};



#endif // H_INITIALIZER
