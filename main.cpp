#include <iostream>

#include "engine/gl.h"
#include "src/Tile.h"
#include "src/GameCycle.h"
#include "engine/render/Window.h"
#include "engine/Log.h"



int main()
{
    std::cout << "HELLOOOOOOOOOO WORLD!!!!" << std::endl;
    
    
    GameCycle *gc = new GameCycle();
    Window window(gc);
    Render *render = new Render();
    window.bindRender(render);
    
    Tile tile(render, Tile::TileType::SOLID, glm::vec3(0.0f));
    Log::inst()->printLog(-1);
    
    window.startWindowCycle();
    
    std::cout << "borks!" << std::endl;
    return 0;
}
