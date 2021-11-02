#include "SnakyController.h"




SnakyController::SnakyController(Snaky *puppet)
    : Timer(Snaky::movingTime()),
      m_puppet(puppet)
{
    
}

void SnakyController::onTick()
{
    m_puppet->finishMovingAnimation();
    
    m_puppet->updateTrajectory();
    Tile *t = m_puppet->getNextTile();
    if (t == nullptr) return; //
    if (t->isSolid()) return; // TODO: destroy snaky
    
    // eating
    if (t->haveFood())
    {
        t->eatFood();
        m_puppet->grow();
    }
    
    // diyng
    if (t->getSnaky().empty() && !t->isPeaceful())
    {
        // TODO: what happens after death
    }
    
    // moving
    m_puppet->move();
    
    m_puppet->startMovingAnimation();
}
