#ifndef H_RENDER
#define H_RENDER



#include <string>

#include "GLM/vec2.hpp"

#include "Camera.h"
#include "RenderingObject.h"

#include "engine/gl.h"

#include "../Log.h"




class Render : public RenderingObject
{

public:
    static Render * inst();
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override {};
    void renderAll();
    void bindCamera(Camera *camera);
    
    glm::vec2 getGLPixelSize() const; 
    glm::ivec2 getWinSize() const {return m_winSize;};
    
private:
    Render();
    static Render *m_instance;
    
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
