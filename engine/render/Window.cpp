#include "engine/render/Window.h"

#include "engine/Log.h"
#include "Render.h"



Window *Window::m_instance = nullptr;



Window * Window::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new Window;
    }
    return m_instance;
}



void Window::addWindowActiveListener(WindowActiveListener *wal)
{
    m_listeners.insert(wal);
}

void Window::revWindowActiveListener(WindowActiveListener *wal)
{
    m_listeners.erase(wal);
}



void Window::startWindowCycle()
{
    while(!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        
        GameCycle::inst()->update(glfwGetTime());
        Render::inst()->renderAll();
        
        glfwSwapBuffers(m_window);
    }
}


glm::ivec2 Window::getSize()
{
    int w, h;
    glfwGetWindowSize(m_window, &w, &h);
    return glm::ivec2(w, h);
}



// private



Window::Window()
{
    glfwSetErrorCallback(errorCalback);
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(640, 640, "Snaky", nullptr, nullptr);
    
    // make the game window square
    int x, y, w, h;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x, &y, &w, &h);
    glfwSetWindowAspectRatio(m_window, 1, 1);
    glfwSetWindowSizeLimits(
                m_window, GLFW_DONT_CARE, GLFW_DONT_CARE, h, h
                            );
    
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    
    glfwSetWindowSizeCallback(m_window, windowSizeCallback);
    glfwSetMouseButtonCallback(m_window, Mouse::onMouseButtonPress);
    glfwSetCursorPosCallback(m_window, Mouse::onCursorMove);
    glfwSetKeyCallback(m_window, Keyboard::onKey);
}



void Window::errorCalback(int error, const char *errorText)
{
    Log::inst()->error(std::to_string(error) + " | " + std::string(errorText));
}

void Window::windowSizeCallback(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);
    for (auto wal : inst()->m_listeners)
    {
        wal->onWindowResize(w, h);
    }
}
