#include "Keyboard.h"

#include "KeyboardListener.h"



Keyboard * Keyboard::m_instance = nullptr;



Keyboard * Keyboard::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new Keyboard;
    }
    return m_instance;
}




void Keyboard::onKey(
        GLFWwindow *window, int key, int scancode, int action, int mods
                  )
{
    switch (action)
    {
    case GLFW_PRESS:
        for (auto kl : inst()->m_listeners)
        {
            kl->onKeyDown(key);
        }
        break;
    case GLFW_REPEAT:
        for (auto kl : inst()->m_listeners)
        {
            kl->onKeyPress(key);
        }
        break;
    case GLFW_RELEASE:
        for (auto kl : inst()->m_listeners)
        {
            kl->onKeyUp(key);
        }
        break;
    }
}
