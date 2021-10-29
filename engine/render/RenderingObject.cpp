#include "RenderingObject.h"



RenderingObject::RenderingObject(Render *render)
    : m_render(render)
{
    m_render->addRenderingObject(this);
}

RenderingObject::~RenderingObject()
{
    m_render->removeRenderingObject(this);
}
