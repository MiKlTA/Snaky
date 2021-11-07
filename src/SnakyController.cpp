#include "SnakyController.h"




SnakyController::SnakyController(Snaky *puppet, Camera *camera, Field *field)
    : Timer(Snaky::movingTime()),
      m_puppet(puppet),
      m_camera(camera),
      m_field(field)
{
    m_camera->setViewSize(glm::vec2(4.0f));
    m_camera->setPos(m_puppet->getHead()->getPos());
}

void SnakyController::onTick(double curTime)
{
    m_puppet->finishMovingAnimation();
    
    m_puppet->repeatTrajectory();
    if (m_puppet->getNextTile() == nullptr) return;
    
    // moving
    Tile *head = m_puppet->getHead();
    
    if (!head->isPeaceful())
        if ((head->haveSnaky() && !head->isSnakyUnique())
                || head->isSolid()
                || m_puppet->isCrossingItself()
                )
        {
            m_puppet->die();
            delete m_puppet;
            m_puppet = nullptr;
            pause();
            return;
        }
    
    m_puppet->move();
    m_camera->setPosWithMoving(
                m_puppet->getHead()->getPos(), Snaky::movingTime()
                               );
    
    // eating
    if (head->haveFood())
    {
        head->eatFood();
        FoodCreator::inst()->decFoodCount();
        m_puppet->grow();
        const int dSnakyLength = 50 - SnakyCreator::initialLength();
        const float dCameraSize = maxCameraSize() - initialCameraSize();
        const float vel = dCameraSize / (dSnakyLength * 1.0f);
        if (m_puppet->size() <= 50)
            m_camera->setViewSizeWithMoving(
                        m_camera->getViewSize() + vel, Snaky::movingTime()
                        );
    }
    
    m_puppet->startMovingAnimation();
}



void SnakyController::onMouseMove(double x, double y)
{
    
    if (m_puppet == nullptr) return;
    const glm::ivec2 windowSize = Window::inst()->getSize();
    const glm::ivec2 mousePos = Mouse::inst()->getPos();
    glm::vec2 nMousePos = glm::intBitsToFloat(mousePos)
            / glm::intBitsToFloat(windowSize - 1);
    glm::vec2 pos = m_camera->convertToWorldCoords(nMousePos);
    
    Tile *tPoint = m_field->getTile(pos);
    if (tPoint != nullptr)
    {
        m_puppet->setTrajectoryPoint(tPoint->getFieldPos());
    }
    
    // DLT: debug output
    /*Log::inst()->message("--------------------------");
    Log::inst()->printLog(1);
    Log::inst()->message(std::to_string(m_camera->getPos().x)
                 + " | "
                 + std::to_string(m_camera->getPos().y));
    Log::inst()->printLog(1);
    Log::inst()->message(std::to_string(pos.x)
                 + " | "
                 + std::to_string(pos.y));
    Log::inst()->printLog(1);*/
}
