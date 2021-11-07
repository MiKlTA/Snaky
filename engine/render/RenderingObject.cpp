#include "RenderingObject.h"



RenderingObject::RenderingObject()
    : m_parent(nullptr),
      m_renderingObjects(),
      m_visible(true)
{
    
}

RenderingObject::RenderingObject(RenderingObject *parent)
    : m_parent(parent),
      m_renderingObjects(),
      m_visible(true)
{
    m_parent->addRenderingObject(this);
}



RenderingObject::~RenderingObject()
{
    if (m_parent != nullptr)
        m_parent->removeRenderingObject(this);
}



void RenderingObject::addRenderingObject(RenderingObject *rObj)
{
    m_renderingObjects.push_back(rObj);
}

void RenderingObject::removeRenderingObject(RenderingObject *rObj)
{
    auto found = std::find(
                m_renderingObjects.begin(), m_renderingObjects.end(), rObj
                           );
    if (found != m_renderingObjects.end())
    {
        m_renderingObjects.erase(found);
    }
}



void RenderingObject::recursiveDraw(
        const glm::mat4 &view, const glm::mat4 &proj
                                    )
{
    draw(view, proj);
    for (auto rObj : m_renderingObjects)
    {
        if (rObj->m_visible)
            rObj->draw(view, proj);
    }
}
