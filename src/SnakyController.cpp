#include "SnakyController.h"




SnakyController::SnakyController(Snaky *puppet)
    : Timer(Snaky::movingTime()),
      m_puppet(puppet)
{
    
}

void SnakyController::onTick()
{
    m_puppet->finishMoving();
    Tile *t = m_puppet->nextTile();
    if (t == nullptr) return; // TODO: destroy snaky
    
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
    
    m_puppet->startMoveNow();
}
