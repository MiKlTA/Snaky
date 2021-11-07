#ifndef H_CAMERA
#define H_CAMERA



#include "GLM/glm.hpp"
#include "GLM/gtx/transform.hpp"

#include "engine/gl.h"
#include "engine/handle/KeyboardListener.h"
#include "engine/handle/Timer.h"
#include "engine/render/WindowActiveListener.h"

#include "../Log.h"



class Camera :
        public KeyboardListener, public Timer,
        public WindowActiveListener
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
    
    void onTick(double curTime) override;
    
    void onWindowResize(int w, int h) override; 
    
    glm::mat4 getView() const;
    const glm::mat4 & getProj() const {return m_proj;};
    
    glm::vec2 getViewSize() const {return m_size;};
    glm::vec2 getPos() const {return m_pos;};
    void setViewSize(glm::vec2 size);
    void setPos(glm::vec2 pos);
    void setViewSizeWithMoving(glm::vec2 newSize, double time);
    void setPosWithMoving(glm::vec2 p, double time);
    
    void block() {m_blocked = true;};
    void unblock() {m_blocked = false;};
    
    // normalized window coordinates to OpenGL space coordinates
    glm::vec2 convertToWorldCoords(glm::vec2 point);
    // on the contrary
    glm::vec2 convertToScreenCoords(glm::vec2 point);
    
private:
    glm::vec3 m_pos;
    const glm::vec3 m_rot;
    glm::vec2 m_size;
    
    glm::mat4 m_proj;
    
    bool m_blocked;
    Moving m_horizontal;
    Moving m_vertical;
    
    bool m_autoMoving;
    Moving m_zoom;
    
    glm::vec2 m_deltaSize;
    double m_zoomingTime;
    double m_maxZoomingTime;
    glm::vec2 m_deltaR;
    double m_movingTime;
    double m_maxMovingTime;
    
    void updProjMat();
    
    static float deltaPos() {return 0.1f;};
    static double updDelay() {return 0.01;};
};



#endif // H_CAMERA
