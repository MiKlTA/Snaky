#include "FoodCreator.h"



FoodCreator *FoodCreator::m_instance = nullptr;



FoodCreator * FoodCreator::inst()
{
    if (m_instance == nullptr)
    {
        m_instance = new FoodCreator;
    }
    return m_instance;
}



void FoodCreator::onTick(double curTime)
{
    if (m_foodCount < m_normalFoodCount)
    {
        createFood();
        m_passing = -1;
    }
    else if (m_foodCount < m_maximumFoodCount)
    {
        if (m_passing == 0)
        {
            createFood();
        }
        ++m_passing;
        if (m_passing == 3) m_passing = 0;
    }
}



void FoodCreator::addFood(Tile *tile)
{
    if (!tile->haveFood())
    {
        tile->addFood();
        m_foodCount++;
    }
}

void FoodCreator::decFoodCount()
{
    if (m_foodCount > 0) --m_foodCount;
}



void FoodCreator::bindField(Field *field)
{
    m_field = field;
}



// private



FoodCreator::FoodCreator()
    : Timer(foodSpawningTime()),
        m_field(nullptr),
        m_normalFoodCount(10),
        m_maximumFoodCount(15),
        m_foodCount(0),
        m_passing(0)
{
    
}



void FoodCreator::createFood()
{
    if (m_field == nullptr) return;
    
    glm::ivec2 size = m_field->getSize();
    
    std::list<glm::ivec2> m_checked;
    while (int(m_checked.size()) < size.x * size.y)
    {
        glm::ivec2 p(rand() % size.x, rand() % size.y);
        auto found = std::find_if(
                    m_checked.begin(), m_checked.end(),
                    [p](const glm::ivec2 &point)
        {
            return p.x == point.x && p.y == point.y;
        });
        if (found != m_checked.end()) continue;
            
        Tile *t = m_field->getTile(p.x, p.y);
        if (t->isSolid() || t->haveFood() || t->haveSnaky() || t->isPeaceful())
        {
            m_checked.push_back(p);
            continue;
        }
        
        addFood(t);
        break;
    }
}
