#include "Render.h"

#include "RenderingObject.h"
#include "Window.h"




Render *Render::m_instance = nullptr;



Render * Render::inst()
{
    if (m_instance == nullptr)
    {
        Window::inst(); // for make a context
        m_instance = new Render;
    }
    return m_instance;
}



void Render::renderAll()
{
    if (m_curCamera == nullptr) return;
    
    glClear(GL_COLOR_BUFFER_BIT);
    glm::mat4 viewMat = m_curCamera->getView();
    glm::mat4 projMat = m_curCamera->getProj();
    recursiveDraw(viewMat, projMat);
}



glm::vec2 Render::getGLPixelSize() const
{
    return m_curCamera->getViewSize() / glm::vec2(m_winSize);
}



// private



void GLAPIENTRY Render::messageCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam
        )
{
    Log::inst()->warning(
                std::string("GL CALLBACK: ")
                + (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "")
                + " type = "
                + std::to_string(type)
                + ", severity = "
                + std::to_string(severity)
                + ", message = "
                + message
                + "\n");
}



// private



Render::Render()
    : m_curCamera(nullptr),
      m_winSize(640, 480)
{
    glewExperimental = true;
    glewInit();
    glClearColor(0.9f, 1.0f, 0.9f, 1.0f);
    
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0);
}
