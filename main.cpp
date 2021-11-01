#include <iostream>
#include <random>

#include "engine/gl.h"
#include "src/Rectangle.h"
#include "src/Field.h"
#include "src/Snaky.h"
#include "src/SnakyController.h"
#include "engine/handle/GameCycle.h"
#include "engine/render/Window.h"
#include "engine/Log.h"

#include "GLM/matrix.hpp"



int main()
{
    std::cout << "HELLOOOOOOOOOO WORLD!!!!" << std::endl;
    
    Camera *camera = new Camera;
    Render::inst()->bindCamera(camera);
    
    Field field(Render::inst(), glm::ivec2(20, 10));
    Tile **tail = new Tile*[9]
    {
        field.getTile(4, 1),
        field.getTile(4, 2),
        field.getTile(3, 2),
        field.getTile(2, 2),
        field.getTile(1, 2),
        field.getTile(1, 3),
        field.getTile(1, 2),
        field.getTile(1, 2),
        field.getTile(1, 1)
    };
    Snaky snaky(
                Render::inst(),
                &field,
                field.getTile(5, 1),
                tail, 9,
                glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
                );
    SnakyController sController(&snaky);
    
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
