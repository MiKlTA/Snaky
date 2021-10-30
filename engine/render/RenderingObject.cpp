#include "RenderingObject.h"



RenderingObject::RenderingObject(Render *render)
    : m_parent(render)
{
    m_parent->addRenderingObject(this);
}

RenderingObject::~RenderingObject()
{
    m_parent->removeRenderingObject(this);
}
