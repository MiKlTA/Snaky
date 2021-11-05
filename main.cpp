#include <iostream>
#include <random>

#include "engine/gl.h"
#include "src/Rectangle.h"
#include "src/Field.h"
#include "src/Snaky.h"
#include "src/SnakyController.h"
#include "src/FoodCreator.h"
#include "engine/handle/GameCycle.h"
#include "engine/render/Window.h"
#include "engine/Log.h"

#include "GLM/matrix.hpp"



int main()
{
    srand(100);
    std::cout << "HELLOOOOOOOOOO WORLD!!!!" << std::endl;
    
    Camera *camera = new Camera;
    Render::inst()->bindCamera(camera);
    
    Field field(Render::inst(), glm::ivec2(50, 30));
    FoodCreator::inst()->bindField(&field);
    Tile **tail = new Tile*[9]
    {
        field.getTile(14, 11),
        field.getTile(14, 12),
        field.getTile(13, 12),
        field.getTile(12, 12),
        field.getTile(11, 12),
        field.getTile(11, 13),
        field.getTile(12, 13),
        field.getTile(13, 13),
        field.getTile(14, 13)
    };
    Snaky *snaky = new Snaky(
                Render::inst(),
                &field,
                field.getTile(15, 11),
                tail, 9,
                glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
                );
    snaky->setTrajectoryPoint(glm::ivec2(20, 10));
    SnakyController sController(snaky, camera, &field);
    
    Rectangle rect(
                Render::inst(), glm::vec4(0.5f, 0.4f, 0.8f, 1.0f),
                glm::vec2(0.0f, 0.0f), glm::vec2(4.0f, 4.0f)
                   );
    rect.stretchBetween(glm::vec2(0.0f, 0.0f), glm::vec2(-2.0f, -1.0f), 0.1f);
    Log::inst()->printLog(-1);
    
    Window::inst()->startWindowCycle();
    
    std::cout << "borks!" << std::endl;
    return 0;
}
