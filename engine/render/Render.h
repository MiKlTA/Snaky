#ifndef H_RENDER
#define H_RENDER



#include <set>
#include <string>

#include "engine/gl.h"

#include "../Log.h"



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
    
    static void GLAPIENTRY messageCallback(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam
            );
    
private:
    std::set<RenderingObject *> m_renderingObjects;
};



#endif // H_RENDER
