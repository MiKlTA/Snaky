#include "Mouse.h"

#include "MouseListener.h"



Mouse * Mouse::m_instance = nullptr;



Mouse * Mouse::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new Mouse;
    }
    return m_instance;
}



void Mouse::onCursorMove(GLFWwindow *window, double x, double y)
{
    inst()->m_Pos.x = x;
    inst()->m_Pos.y = y;
    
    for (auto ml : inst()->m_listeners)
    {
        ml->onMouseMove(x, y);
    }
}

void Mouse::onMouseButtonPress(
        GLFWwindow *window, int button, int action, int mods
                               )
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            for (auto ml : inst()->m_listeners)
            {
                ml->onMouseLeftClick();
            }
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            for (auto ml : inst()->m_listeners)
            {
                ml->onMouseRightClick();
            }
            break;
        }
    }
}
