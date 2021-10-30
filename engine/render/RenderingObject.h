#ifndef H_RENDERING_OBJECT
#define H_RENDERING_OBJECT



#include "Render.h"

#include "GLM/matrix.hpp"




class RenderingObject
{

public:
    RenderingObject(Render *render);
    virtual ~RenderingObject();
    
    virtual void draw(const glm::mat4 &view, const glm::mat4 &proj) = 0;
    
private:
    Render *m_parent;
};







#endif // H_RENDERING_OBJECT
