#include "Render.h"

#include "RenderingObject.h"



Render::Render()
{
    glewExperimental = true;
    glewInit();
    glClearColor(0.7f, 0.5f, 0.3f, 1.0f);
    
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(messageCallback, 0);
}



void Render::renderAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto rObj : m_renderingObjects)
    {
        rObj->draw(glm::mat4(1.0f), glm::mat4(1.0f));
    }
}

void Render::addRenderingObject(RenderingObject *rObj)
{
    m_renderingObjects.insert(rObj);
}

void Render::removeRenderingObject(RenderingObject *rObj)
{
    m_renderingObjects.erase(rObj);
}



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
