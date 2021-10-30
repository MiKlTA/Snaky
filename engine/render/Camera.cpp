#include "Camera.h"

#include "Render.h"



Camera::Camera()
    : Timer(updDelay()),
      m_pos(0.0f, 0.0f, -1.0f),
      m_rot(0.0f),
      m_size(1.0f),
      // TODO: change to 0.5f
      m_proj(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f)),
      m_horizontal(Moving::NONE),
      m_vertical(Moving::NONE)
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
        m_size.x *= 1.1f;
        m_proj = glm::ortho(
                    -m_size.x/2.0f, m_size.x/2.0f,
                    -m_size.x/2.0f, m_size.x/2.0f
                    );
        break;
    case GLFW_KEY_E:
        m_size.x /= 1.1f;
        m_proj = glm::ortho(
                    -m_size.x/2.0f, m_size.x/2.0f,
                    -m_size.x/2.0f, m_size.x/2.0f
                    );
        break;
    }
}

void Camera::onKeyUp(int key)
{
    switch (key)
    {
    case GLFW_KEY_W:
    case GLFW_KEY_S:
        m_vertical = Moving::NONE;
        break;
    case GLFW_KEY_D:
    case GLFW_KEY_A:
        m_horizontal = Moving::NONE;
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
