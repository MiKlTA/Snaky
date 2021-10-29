#ifndef H_WINDOW
#define H_WINDOW



// Is engaged in setting up the rendering and cycle control



#include <iostream>

#include "engine/gl.h"

#include "../Log.h"

#include "IGameCycle.h"
#include "../handle/Mouse.h"
#include "../handle/Keyboard.h"
#include "Render.h"



class Window
{

public:
    Window(IGameCycle *gameCycle);
    
	void startWindowCycle();
    
    void bindRender(Render *render);
    void bindMouse(Mouse *mouse);
    void bindKeyboard(Keyboard *keyboard);
	
private:
    GLFWwindow *m_window;
    
    IGameCycle *m_gameCycle;
    Render *m_render;
    
    static void errorCalback(int error, const char *errorText);
};



#endif // H_WINDOW
