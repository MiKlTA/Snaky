#ifndef H_FIELD
#define H_FIELD



#include <set>
#include <math.h>

#include "GLM/matrix.hpp"

#include "../engine/render/RenderingObject.h"
#include "./engine/etc/Direction.h"

#include "Tile.h"



class Field : public RenderingObject
{
public:
    Field(Render *render, glm::ivec2 size);
    ~Field();
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    Tile * getTile(int x, int y) {return m_tiles[x][y];};
    Tile ** getTilesNear(const Tile *tile, int &count);
    Tile * getTileByDir(const Tile *tile, Direction dir);
    Tile * getTileOnLine(glm::ivec2 startPoint, float tanAngle, int n);
    Tile * getTileOn();
    
    void moveSnaky(); // TODO:
    
    static glm::vec3 getTilePos(int x, int y);
    static float distance() {return 0.08f;};
    
private:
    glm::ivec2 m_size;
    Tile ***m_tiles;
    
    static float sqrt3d2() {return std::sqrt(3.0f)/2.0f;};
    static float xDelta() {return sqrt3d2() * distance() + 0.5f;};
    static float yDelta() {return 1.5f * distance() + sqrt3d2();};
};



#endif // H_FIELD
