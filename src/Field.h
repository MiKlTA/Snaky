#ifndef H_FIELD
#define H_FIELD



#include <set>
#include <math.h>

#include "GLM/matrix.hpp"

#include "../engine/render/RenderingObject.h"
//#include "../engine/render/Shader.h"
//#include "../engine/render/ShaderProgram.h"
#include "./engine/etc/Direction.h"

#include "Tile.h"



class Field : public RenderingObject
{
public:
    Field(Render *render, glm::ivec2 size);
    ~Field();
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    Tile ** getTilesNear(const Tile *tile, int &count);
    Tile * getTileByDir(const Tile *tile, Direction dir);
    void moveSnaky(); // TODO:
    
    static glm::vec3 getTilePos(int x, int y);
    static float getDistance() {return 0.08f;};
    
private:
    glm::ivec2 m_size;
    Tile ***m_tiles;
    
    Tile * getTile(int x, int y) {return m_tiles[x][y];};
};



#endif // H_FIELD
