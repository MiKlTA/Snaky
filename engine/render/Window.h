#ifndef H_WINDOW
#define H_WINDOW



// Is engaged in setting up the rendering and cycle control



#include <iostream>

#include "engine/gl.h"

#include "IGameCycle.h"
#include "Render.h"
#include "../handle/Mouse.h"



class Window
{

public:
    Window(IGameCycle *gameCycle, Render *render);
    
	void startWindowCycle();
    
    void bindMouse(Mouse *mouse);
	
private:
    GLFWwindow *m_window;
    
    IGameCycle *m_gameCycle;
    Render *m_render;
    
    static void errorCalback(int error, const char *errorText);
};



#endif // H_WINDOW
