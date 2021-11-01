#include "Camera.h"

#include "Render.h"



Camera::Camera()
    : Timer(updDelay()),
      m_pos(0.0f, 0.0f, -1.0f),
      m_rot(0.0f),
      // TODO: change to 1.0f
      m_size(10.0f),
      // TODO: change to 0.5f
      m_proj(glm::ortho(
                 -m_size.x/2.0f, m_size.x/2.0f,
                 -m_size.y/2.0f, m_size.y/2.0f
                 )),
      m_horizontal(Moving::NONE),
      m_vertical(Moving::NONE),
      m_zoom(Moving::NONE)
{
    
}



void Camera::onKeyDown(int key)
{
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



void Camera::onTick()
{
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
        m_size.x *= 1.03f;
        m_proj = glm::ortho(
                    -m_size.x/2.0f, m_size.x/2.0f,
                    -m_size.x/2.0f, m_size.x/2.0f
                    );
    }
    else if (m_zoom == Moving::BACK)
    {
        m_size.x /= 1.03f;
        m_proj = glm::ortho(
                    -m_size.x/2.0f, m_size.x/2.0f,
                    -m_size.x/2.0f, m_size.x/2.0f
                    );
    }
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
