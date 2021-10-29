#include "engine/render/Window.h"

#include "engine/Log.h"



Window::Window(IGameCycle *gameCycle)
    : m_gameCycle(gameCycle),
      m_render(nullptr)
{
    glfwSetErrorCallback(errorCalback);
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(640, 480, "Snaky", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
}



void Window::startWindowCycle()
{
    if (m_render == nullptr)
    {
        Log::inst()->warning("Render is not set!");
        return;
    }
    while(!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        
        
        
        m_gameCycle->update();
        m_render->renderAll();
        
        glfwSwapBuffers(m_window);
    }
}



void Window::bindRender(Render *render)
{
    m_render = render;
}

void Window::bindMouse(Mouse *mouse)
{
    
}

void Window::bindKeyboard(Keyboard *keyboard)
{
    
}



// private



void Window::errorCalback(int error, const char *errorText)
{
    Log::inst()->error(std::to_string(error) + " | " + std::string(errorText));
}
