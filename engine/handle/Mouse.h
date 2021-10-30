#ifndef H_MOUSE
#define H_MOUSE



#include <set>

#include "GLM/vec2.hpp"

#include "engine/gl.h"



class MouseListener;



class Mouse
{

public:
    static Mouse * inst();
    
    void addListener(MouseListener *ml) {m_listeners.insert(ml);};
    void remListener(MouseListener *ml) {m_listeners.erase(ml);};
    
    static void onCursorMove(GLFWwindow *window, double x, double y);
    static void onMouseButtonPress(
            GLFWwindow *window, int button, int action, int mods
                                   );
    
    const glm::dvec2 & getPos() const {return m_Pos;};
    
private:
    Mouse() {};
    
    static Mouse * m_instance;
    glm::dvec2 m_Pos;
    std::set<MouseListener *> m_listeners;
};



#endif // H_MOUSE
