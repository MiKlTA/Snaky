#ifndef H_WINDOW
#define H_WINDOW



// Is engaged in setting up the rendering and cycle control



#include <iostream>
#include <set>

#include "WindowActiveListener.h"

#include "engine/gl.h"

#include "../Log.h"

#include "../handle/GameCycle.h"
#include "../handle/Mouse.h"
#include "../handle/Keyboard.h"



class Window
{

public:
    static Window * inst();
    
    void addWindowActiveListener(WindowActiveListener *wal);
    void revWindowActiveListener(WindowActiveListener *wal);
    
	void startWindowCycle();
	
private:
    Window();
    static Window *m_instance;
    
    std::set<WindowActiveListener *> m_listeners;
    
    GLFWwindow *m_window;
    
    static void errorCalback(int error, const char *errorText);
    static void windowSizeCallback(GLFWwindow *window, int w, int h);
    
};



#endif // H_WINDOW
