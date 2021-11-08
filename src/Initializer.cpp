#include "Initializer.h"



Initializer *Initializer::m_instance = nullptr;



Initializer *Initializer::init()
{
    if (m_instance == nullptr)
    {
        m_instance = new Initializer;
    }
    return m_instance;
}



void Initializer::startGameCycle()
{
    m_window->startWindowCycle();
}



// private:



Initializer::Initializer()
    : m_window(nullptr),
      m_render(nullptr),
      m_camera(nullptr),
      
      m_field(nullptr),
      m_foodCreator(nullptr),
      m_snakyCreator(nullptr)
{
    srand(127);
    m_window = Window::inst();
    m_render = Render::inst();
    m_camera = new Camera;
    
    m_field = new Field(m_render, m_camera, fieldSize());
    m_foodCreator = FoodCreator::inst();
    m_snakyCreator = SnakyCreator::inst();
    
    _init();
}



void Initializer::_init()
{
    m_camera->block();
    m_render->bindCamera(m_camera);
    
    m_foodCreator->bindField(m_field);
    m_foodCreator->setNormalFoodCount(normalFoodCount());
    m_foodCreator->setMaximumFoodCount(maximumFoodCount());
    
    m_snakyCreator->bindField(m_field);
    m_snakyCreator->setSpawnArea(
                glm::ivec2(Field::solidZone().x, Field::solidZone().y),
                glm::ivec2(
                    Field::solidZone().x + Field::peacefulZone(),
                    m_field->getSize().y - Field::solidZone().y
                           ) );
    
    // Warning!
    Snaky *snaky = m_snakyCreator->getProduct();
    SnakyController *sController
            = new SnakyController(snaky, m_camera, m_field);
    Log::inst()->printLog(-1);
}
