#ifndef H_RENDERING_OBJECT
#define H_RENDERING_OBJECT



#include "Render.h"





class RenderingObject
{

public:
    RenderingObject(Render *render) {m_render = render;};
    
    virtual void draw() = 0;
    
private:
    Render *m_render;
    
};







#endif // H_RENDERING_OBJECT
