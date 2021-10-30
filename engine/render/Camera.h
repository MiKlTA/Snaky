#ifndef H_CAMERA
#define H_CAMERA



#include "GLM/glm.hpp"
#include "GLM/gtx/transform.hpp"

#include "engine/gl.h"
#include "engine/handle/KeyboardListener.h"
#include "engine/handle/Timer.h"
#include "engine/render/WindowActiveListener.h"

#include "../Log.h"



class Camera
        : public KeyboardListener, public Timer, public WindowActiveListener
{

public:
    enum class Moving
    {
        BACK,
        NONE,
        FORWARD
    };
    
    Camera();
    
    void onKeyDown(int key) override;
    void onKeyUp(int key) override;
    
    void onTick() override;
    
    void onWindowResize(int w, int h) override; 
    
    glm::mat4 getView() const;
    const glm::mat4 & getProj() const {return m_proj;};
    
    glm::vec2 getViewSize() const {return m_size;};
    void setViewSize(float w, float h);
    
private:
    glm::vec3 m_pos;
    const glm::vec3 m_rot;
    glm::vec3 m_size;
    
    glm::mat4 m_proj;
    
    Moving m_horizontal;
    Moving m_vertical;
    
    static float deltaPos() {return 0.1f;};
    static double updDelay() {return 0.01;};
};



#endif // H_CAMERA
