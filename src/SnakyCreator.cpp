#include "SnakyCreator.h"



SnakyCreator *SnakyCreator::m_instance = nullptr;



SnakyCreator * SnakyCreator::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new SnakyCreator;
    }
    return m_instance;
}



void SnakyCreator::setSpawnArea(glm::ivec2 p1, glm::ivec2 p2)
{
    if (p2.x - p1.x < 2 * safeDistance() + 1
            || p2.y - p1.y < 2 * safeDistance() + 1)
        return;
    if (p1.x < 0) p1.x = 0;
    if (p1.y < 0) p1.y = 0;
    const glm::ivec2 &size = m_field->getSize();
    if (p2.x >= size.x) p2.x = size.x;
    if (p2.y >= size.y) p2.y = size.y;
    m_sAPoint1 = p1;
    m_sAPoint2 = p2;
}



void SnakyCreator::build()
{
    const glm::ivec2 &size = m_sAPoint2 - m_sAPoint1 + 1;
    int x = rand() % (size.x - initialLength()) + (m_sAPoint1.x + initialLength());
    int y = rand() % (size.y) + (m_sAPoint1.y);
    
    Tile *head = m_field->getTile(x, y);
    std::vector<Tile *> tail;
    
    glm::vec4 color = glm::vec4(
                1.0f * (rand() % 2),
                1.0f * (rand() % 2),
                1.0f * (rand() % 2),
                1.0f
                                );
    
    for (int i = 0; i < initialLength() - 1; ++i)
    {
        tail.push_back(m_field->getTile(x - i - 1, y));
    }
    
    m_product = new Snaky(
                Render::inst(), m_field,
                head, tail.data(), tail.size(), color
                );
    m_product->setTrajectoryPoint(glm::ivec2(x + 1, y));
}

Snaky * SnakyCreator::getProduct()
{
    if (m_product == nullptr)
    {
        build();
    }
    return m_product;
}



// private



SnakyCreator::SnakyCreator()
    : m_product(nullptr),
      
      m_field(nullptr),
      m_sAPoint1(0),
      m_sAPoint2(0)
{
    
}
