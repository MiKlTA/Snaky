#ifndef H_KEYBOARD
#define H_KEYBOARD



#include <set>

#include "GLM/vec2.hpp"

#include "engine/gl.h"



class KeyboardListener;



class Keyboard
{

public:
    static Keyboard * inst();
    
    void addListener(KeyboardListener *ml) {m_listeners.insert(ml);};
    void remListener(KeyboardListener *ml) {m_listeners.erase(ml);};
    
    static void onKey(
            GLFWwindow *window, int key, int scancode, int action, int mods
                      );
    
    const glm::dvec2 & getPos() const {return m_Pos;};
    
private:
    Keyboard() {};
    
    static Keyboard * m_instance;
    glm::dvec2 m_Pos;
    std::set<KeyboardListener *> m_listeners;
};



#endif // H_KEYBOARD
