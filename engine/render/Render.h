#ifndef H_RENDER
#define H_RENDER



#include <set>
#include <string>

#include "GLM/vec2.hpp"

#include "Camera.h"

#include "engine/gl.h"

#include "../Log.h"



// this class is responsible for the complete preparation for the
// rendering of all objects, as well as for their registration



class RenderingObject;



class Render
{

public:
    static Render * inst();
    
    void renderAll();
    void addRenderingObject(RenderingObject *rObj);
    void removeRenderingObject(RenderingObject *rObj);
    void bindCamera(Camera *camera);
    
    glm::vec2 getGLPixelSize() const; 
    glm::ivec2 getWinSize() const {return m_winSize;};
    
private:
    Render();
    static Render *m_instance;
    
    std::set<RenderingObject *> m_renderingObjects;
    Camera *m_curCamera;
    
    glm::ivec2 m_winSize;
    
    static void GLAPIENTRY messageCallback(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam
            );
};



#endif // H_RENDER
