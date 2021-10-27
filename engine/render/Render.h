#ifndef H_RENDER
#define H_RENDER



#include <set>

#include "Shader.h"
#include "engine/gl.h"



// this class is responsible for the complete preparation for the
// rendering of all objects, as well as for their registration



class RenderingObject;



class Render
{

public:
    Render();
    
    void renderAll();
    void addRenderingObject(RenderingObject *rObj);
    void removeRenderingObject(RenderingObject *rObj);
    
    
    
private:
    std::set<RenderingObject *> m_renderingObjects;
};



#endif // H_RENDER
