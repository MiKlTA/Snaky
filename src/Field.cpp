#include "Field.h"



Field::Field(Render *render, glm::ivec2 size)
    : RenderingObject(render),
      m_size(size),
      m_tiles(new Tile**[size.x])
{
    for (int x = 0; x < m_size.x; ++x)
    {
        m_tiles[x] = new Tile*[m_size.y];
        for (int y = 0; y < m_size.y; ++y)
        {
            m_tiles[x][y] = new Tile(
                        render, Tile::TileType::VOID, glm::ivec2(x, y),
                        false, (x + y) % 2 != 0
                                     );
        }
    }
}

Field::~Field()
{
    for (int x = 0; x < m_size.x; ++x)
    {
        for (int y = 0; y < m_size.y; ++y)
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
        for (int y = 0; y < m_size.y; ++y)
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
    
    return res;
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
    
    return nullptr;
}

Tile * Field::getTileOnLine(glm::ivec2 startPoint, float tanAngle, int n)
{
    // TODO: does not work with tanAngle > 1.
    // It should be reduced to the case with tanAngle < 1
    
    // y(n) = tanAngle * (n + startPoint.x) + startPoint.y
    int targetX = n + startPoint.x;
    int targetY = std::round(tanAngle * targetX) + startPoint.y;
    if (targetY >= m_size.y || targetX >= m_size.x)
        return nullptr;
    else
        return m_tiles[targetX][targetY];
}



glm::vec3 Field::getTilePos(int x, int y)
{
    const float d = distance();
    return glm::vec3(
                xDelta() * x,
                0.5f * d * ((x + y) % 2) + yDelta() * y,
                0.0f
                     );
}
