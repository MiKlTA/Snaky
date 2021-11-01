#include <iostream>
#include <random>

#include "engine/gl.h"
#include "src/Rectangle.h"
#include "src/Field.h"
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
