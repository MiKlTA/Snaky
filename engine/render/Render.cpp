#include "Render.h"

#include "RenderingObject.h"



Render::Render()
{
    glewExperimental = true;
    glewInit();
    glClearColor(0.7f, 0.5f, 0.3f, 1.0f);
}



void Render::renderAll()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto rObj : m_renderingObjects)
    {
        rObj->draw();
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
