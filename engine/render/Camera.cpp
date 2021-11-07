#include "Camera.h"

#include "Render.h"



Camera::Camera()
    : Timer(updDelay()),
      m_pos(10.0f, 10.0f, -1.0f),
      m_rot(0.0f),
      m_size(1.0f),
      m_proj(glm::ortho(
                 -m_size.x/2.0f, m_size.x/2.0f,
                 -m_size.y/2.0f, m_size.y/2.0f,
                 -100.0f, 100.0f
                 )),
      
      m_blocked(false),
      m_horizontal(Moving::NONE),
      m_vertical(Moving::NONE),
      
      m_autoMoving(false),
      m_zoom(Moving::NONE),
      
      m_deltaSize(0.0f),
      m_zoomingTime(0.0),
      m_maxZoomingTime(0.0),
      m_deltaR(0.0),
      m_movingTime(0.0),
      m_maxMovingTime(0.0)
{
    
}



void Camera::onKeyDown(int key)
{
    if (m_blocked) return;
    
    switch (key)
    {
    case GLFW_KEY_W:
        m_vertical = Moving::FORWARD;
        break;
    case GLFW_KEY_S:
        m_vertical = Moving::BACK;
        break;
    case GLFW_KEY_D:
        m_horizontal = Moving::FORWARD;
        break;
    case GLFW_KEY_A:
        m_horizontal = Moving::BACK;
        break;
    // TODO: remove it
    case GLFW_KEY_Q:
        m_zoom = Moving::FORWARD;
        break;
    case GLFW_KEY_E:
        m_zoom = Moving::BACK;
        break;
    }
}

void Camera::onKeyUp(int key)
{
    if (m_blocked) return;
    
    switch (key)
    {
    case GLFW_KEY_W:
        if (m_vertical == Moving::FORWARD)
            m_vertical = Moving::NONE;
        break;
    case GLFW_KEY_S:
        if (m_vertical == Moving::BACK)
            m_vertical = Moving::NONE;
        break;
    case GLFW_KEY_D:
        if (m_horizontal == Moving::FORWARD)
            m_horizontal = Moving::NONE;
        break;
    case GLFW_KEY_A:
        if (m_horizontal == Moving::BACK)
            m_horizontal = Moving::NONE;
        break;
        // DLT:
    case GLFW_KEY_Q:
        if (m_zoom == Moving::FORWARD)
            m_zoom = Moving::NONE;
        break;
    case GLFW_KEY_E:
        if (m_zoom == Moving::BACK)
            m_zoom = Moving::NONE;
        break;
    }
}



void Camera::onTick(double curTime)
{
    static double lastTime;
    const double dt = curTime - lastTime;
    if (m_autoMoving)
    {
        const glm::vec2 dr = m_deltaR * float(dt / m_maxMovingTime);
        m_pos.x += dr.x;
        m_pos.y += dr.y;
        m_movingTime += dt;
        if (m_movingTime > m_maxMovingTime)
        {
            m_movingTime = m_maxMovingTime;
            m_autoMoving = false;
        }
    }
    if (m_zoom != Moving::NONE)
    {
        m_size += m_deltaSize * float(dt / m_maxZoomingTime);
        updProjMat();
        m_zoomingTime += dt;
        if (m_zoomingTime > m_maxZoomingTime)
        {
            m_zoomingTime = 0.0;
            m_zoom = Moving::NONE;
        }
    }
    if (m_autoMoving || m_zoom != Moving::NONE)
    {
        lastTime = curTime;
        return;
    }
    
    if (m_horizontal == Moving::FORWARD)
    {
        m_pos.x += deltaPos();
    }
    else if (m_horizontal == Moving::BACK)
    {
        m_pos.x -= deltaPos();
    }
    
    if (m_vertical == Moving::FORWARD)
    {
        m_pos.y += deltaPos();
    }
    else if (m_vertical == Moving::BACK)
    {
        m_pos.y -= deltaPos();
    }
    
    // DLT:
    if (m_zoom == Moving::FORWARD)
    {
        m_size *= 1.03f;
        updProjMat();
    }
    else if (m_zoom == Moving::BACK)
    {
        m_size /= 1.03f;
        updProjMat();
    }
    
    lastTime = curTime;
}



void Camera::onWindowResize(int w, int h)
{
    // if necessary, you can make the window always proportional
    //m_size.x = w / (h * 1.0f);
    //m_proj = glm::ortho(-m_size.x / 2.0f, m_size.x / 2.0f, -0.5f, 0.5f);
}



glm::mat4 Camera::getView() const
{
    return glm::translate(glm::mat4(1.0f), -m_pos);
}



void Camera::setViewSize(glm::vec2 size)
{
    m_size.x = size.x;
    m_size.y = size.y;
    updProjMat();
}

void Camera::setPos(glm::vec2 pos)
{
    m_pos.x = pos.x;
    m_pos.y = pos.y;
    updProjMat();
}

void Camera::setViewSizeWithMoving(glm::vec2 newSize, double time)
{
    m_zoom = Moving::FORWARD;
    m_deltaSize = newSize - m_size;
    m_zoomingTime = 0.0;
    m_maxZoomingTime = time;
}

void Camera::setPosWithMoving(glm::vec2 p, double time)
{
    m_autoMoving = true;
    m_deltaR = p - glm::vec2(m_pos);
    m_movingTime = 0.0;
    m_maxMovingTime = time;
}



glm::vec2 Camera::convertToWorldCoords(glm::vec2 point)
{
    point.y = 1.0f - point.y;
    point -= 0.5f;
    
    point.x *= m_size.x;
    point.y *= m_size.y;
    
    point.x += m_pos.x;
    point.y += m_pos.y;
    
    return point;
}

glm::vec2 Camera::convertToScreenCoords(glm::vec2 point)
{
    
}



// private:



void Camera::updProjMat()
{
    m_proj = glm::ortho(
                -m_size.x/2.0f, m_size.x/2.0f,
                -m_size.y/2.0f, m_size.y/2.0f,
                -100.0f, 100.0f
                );
}
