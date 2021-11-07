#include <iostream>
#include <random>

#include "engine/gl.h"
#include "src/Rectangle.h"
#include "src/Field.h"
#include "src/Snaky.h"
#include "src/SnakyCreator.h"
#include "src/SnakyController.h"
#include "src/FoodCreator.h"
#include "engine/handle/GameCycle.h"
#include "engine/render/Window.h"
#include "engine/Log.h"

#include "GLM/matrix.hpp"


#include <ctime>


int main()
{
    srand(127);
    std::cout << "HELLOOOOOOOOOO WORLD!!!!" << std::endl;
    
    Camera *camera = new Camera;
    camera->block();
    Render::inst()->bindCamera(camera);
    
    Field *field = new Field(Render::inst(), camera, glm::ivec2(20, 20));
    FoodCreator::inst()->bindField(field);
    FoodCreator::inst()->setNormalFoodCount(100);
    FoodCreator::inst()->setNormalFoodCount(100);
    
    SnakyCreator::inst()->setField(field);
    SnakyCreator::inst()->setSpawnArea(
                glm::ivec2(Field::solidZone().x, Field::solidZone().y),
                glm::ivec2(Field::solidZone().x + Field::peacefulZone(),
                           field->getSize().y - Field::solidZone().y)
                );
    Snaky *snaky = SnakyCreator::inst()->getProduct();
    SnakyController sController(snaky, camera, field);
    
    Log::inst()->printLog(-1);
    Window::inst()->startWindowCycle();
    
    std::cout << "borks!" << std::endl;
    return 0;
}
