#include "Field.h"



Field::Field(Render *render, glm::ivec2 size)
    : RenderingObject(render),
      m_size(size),
      m_tiles(new Tile**[m_size.x])
{
    for (int x = 0; x < m_size.x; ++x)
    {
        m_tiles[x] = new Tile*[m_size.y];
        for (int y = 0; y < m_size.x; ++y)
        {
            m_tiles[x][y] = new Tile(
                        render, Tile::TileType::VOID,
                        getTilePos(x, y), (x + y) % 2 != 0
                                     );
        }
    }
}

Field::~Field()
{
    for (int x = 0; x < m_size.x; ++x)
    {
        for (int y = 0; y < m_size.x; ++y)
        {
            delete m_tiles[x][y];
        }
        delete[] m_tiles[x];
    }
    delete[] m_tiles;
}



void Field::draw(const glm::mat4 &view, const glm::mat4 &proj)
{
    for (int x = 0; x < m_size.x; ++x)
        for (int y = 0; y < m_size.x; ++y)
        {
            m_tiles[x][y]->draw(view, proj);
        }
}



Tile ** Field::getTilesNear(const Tile *tile, int &count)
{
    count = 0;
    Tile **res;
    const int x = tile->getFieldPos().x;
    const int y = tile->getFieldPos().y;
    
    if (x != 0)
    {
        res[count] = getTile(x - 1, y);
        count++;
    }
    if (x != m_size.x - 1)
    {
        res[count] = getTile(x + 1, y);
        count++;
    }
    if (!tile->isInverted() && y != 0)
    {
        res[count] = getTile(x, y - 1);
        count++;
    }
    else if (y != m_size.y - 1)
    {
        res[count] = getTile(x, y + 1);
        count++;
    }
}

Tile * Field::getTileByDir(const Tile *tile, Direction dir)
{
    const int x = tile->getFieldPos().x;
    const int y = tile->getFieldPos().y;
    
    switch (dir)
    {
    case Direction::UP:
        if (x != 0)
        {
            return getTile(x - 1, y);
        }
        break;
    case Direction::RIGHT:
        if (x != m_size.x - 1)
        {
            return getTile(x + 1, y);
        }
        break;
    case Direction::DOWN:
        if (!tile->isInverted() && y != 0)
        {
            return getTile(x, y - 1);
        }
        break;
    case Direction::LEFT:
        if (y != m_size.y - 1)
        {
            return getTile(x, y + 1);
        }
        break;
    }
}



glm::vec3 Field::getTilePos(int x, int y)
{
    const float d = getDistance();
    static const float sqrt3d2 = std::sqrt(3.0f)/2.0f;
    return glm::vec3(
                (sqrt3d2 * d + 0.5f) * x,
                0.5f * d * ((x + y) % 2) + (1.5f * d + sqrt3d2) * y,
                0.0f
                     );
}
