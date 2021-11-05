#include "SnakyController.h"




SnakyController::SnakyController(Snaky *puppet, Camera *camera, Field *field)
    : Timer(Snaky::movingTime()),
      m_puppet(puppet),
      m_camera(camera),
      m_field(field)
{
    
}

void SnakyController::onTick()
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
    
    // eating
    if (head->haveFood())
    {
        head->eatFood();
        FoodCreator::inst()->decFoodCount();
        m_puppet->grow();
    }
    
    m_puppet->startMovingAnimation();
}



void SnakyController::onMouseLeftClick()
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
