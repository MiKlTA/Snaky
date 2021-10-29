#ifndef H_CAMERA
#define H_CAMERA



#include "GLM/vec3.hpp"

#include "engine/gl.h"
#include "engine/handle/KeyboardListener.h"

#include "../Log.h"



class Camera : public KeyboardListener
{

public:
    Camera();
    
    void onKeyDown(int key) override;
    void onKeyUp(int key) override;
    
private:
    glm::vec3 m_pos;
    const glm::vec3 m_rot;
    glm::vec3 m_scale;
};



#endif // H_CAMERA
