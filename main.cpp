#include <iostream>

#include "engine/gl.h"
#include "src/Tile.h"
#include "engine/handle/GameCycle.h"
#include "engine/render/Window.h"
#include "engine/Log.h"



int main()
{
    std::cout << "HELLOOOOOOOOOO WORLD!!!!" << std::endl;
    
    Camera *camera = new Camera;
    Render::inst()->bindCamera(camera);
    
    Tile tile(Render::inst(), Tile::TileType::SOLID, true);
    Tile tile2(Render::inst(), Tile::TileType::SOLID, false);
    tile2.setPos(0.5f, 0.0f);
    Log::inst()->printLog(-1);
    
    Window::inst()->startWindowCycle();
    
    std::cout << "borks!" << std::endl;
    return 0;
}
