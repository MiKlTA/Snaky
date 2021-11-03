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



Tile * Field::getTile(int x, int y)
{
    if (x < 0 || y < 0 || x >= m_size.x || y >= m_size.y)
        return nullptr;
    else
        return m_tiles[x][y];
}

Tile * Field::getTile(glm::vec2 pos)
{
    glm::ivec2 fieldPos;
    fieldPos.x = (pos.x / xDelta() + 0.5f);
    fieldPos.y = (pos.y / yDelta() + 0.5f);
    // DLT: debug output
    /*Log::inst()->message(std::to_string(fieldPos.x)
                         + " | "
                         + std::to_string(fieldPos.y));
    Log::inst()->printLog(1);*/
    return getTile(fieldPos.x, fieldPos.y);
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
        if (tile->isInverted() && y != m_size.y - 1)
        {
            return getTile(x, y + 1);
        }
        break;
    case Direction::RIGHT:
        if (x != m_size.x - 1)
        {
            Tile *myTile = nullptr;
            myTile = getTile(x + 1, y);
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
        if (x != 0)
        {
            return getTile(x - 1, y);
        }
        break;
    }
    
    return nullptr;
}

bool Field::canMoveDirectlyTo(const Tile *from, const Tile *to)
{
    if (getTileByDir(from, Direction::UP) == to && from->isInverted())
        return true;
    if (getTileByDir(from, Direction::RIGHT) == to) return true;
    if (getTileByDir(from, Direction::DOWN) == to && !from->isInverted())
        return true;
    if (getTileByDir(from, Direction::LEFT) == to) return true;
    return false;
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
