#include "Snaky.h"

#include "Field.h"

// DLT:
#include <random>



bool Snaky::m_modelIsDone = false;
GLfloat *Snaky::m_modelsVertices = nullptr;
unsigned int Snaky::m_modelsVerticesCount = 0;
GLuint Snaky::m_VBO = 0;
GLuint Snaky::m_VAO = 0;
ShaderProgram *Snaky::m_shaderProgram = nullptr;
GLuint Snaky::m_modelMatLoc = 0;
GLuint Snaky::m_viewMatLoc = 0;
GLuint Snaky::m_projMatLoc = 0;
GLuint Snaky::m_colorLoc = 0;
GLuint Snaky::m_centrePosLoc = 0;




Snaky::Snaky(
        Render *render, Field *field, Tile *head,
        Tile **tail, int tailLength,
        glm::vec4 color
             )
    : RenderingObject(render),
      Timer(movingTime() / (1.0 * stageOfMoving())),
      m_field(field),
      m_head(head),
      m_tail(),
      
      m_isGrowing(false),
      m_isMovingAnimation(false),
      m_trajectory(),
      m_relTargetPoint(0.0f),
      
      m_rot(maxAngle()),
      
      m_model(1.0f),
      m_color(color)
{
    for (int i = 0; i < tailLength; ++i)
    {
        m_tail.push_back(tail[i]);
    }
    
    makeModel();
    
    startMovingAnimation();
}

Snaky::~Snaky()
{
    die();
    
    delete[] m_modelsVertices;
    delete m_shaderProgram;
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_VAO);
}



void Snaky::draw(const glm::mat4 &view, const glm::mat4 &proj)
{
    glBindVertexArray(m_VAO);
    m_shaderProgram->use();
    glUniformMatrix4fv(m_viewMatLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projMatLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform4fv(m_colorLoc, 1, &m_color[0]);
    // TODO: make a gradient!!!
    
    if (m_isMovingAnimation)
    {
        drawMovingPiece(m_tail.front(), m_head, m_rot);
        if (m_tail.size() > 1 && !m_isGrowing)
        {
            drawMovingPiece(
                        *std::prev(m_tail.end(), 2),
                        m_tail.back(),
                        maxAngle() - m_rot
                        );
        }
    }
    else
        drawPiece(m_head);
    for (auto i = m_tail.begin(); i != m_tail.end(); ++i)
    {
        if (m_tail.size() > 1
                && i == std::prev(m_tail.end(), 1)
                && !m_isGrowing)
            break;
        drawPiece(*i);
    }
}



void Snaky::onTick()
{
    m_rot -= deltaAngle();
}



Tile * Snaky::getNextTile()
{
    if (m_trajectory.empty()) return nullptr;
    return m_trajectory.back();
}

void Snaky::move()
{
    if (m_trajectory.empty()) return;
    Tile *back = m_trajectory.back();
    // DLT:
//    Log::inst()->message(
//                std::to_string(back->getFieldPos().x)
//                + " | "
//                + std::to_string(back->getFieldPos().y)
//                );
    Log::inst()->printLog(1);
    m_trajectory.pop_back();
    back->addSnaky(this);
    m_tail.push_front(m_head);
    m_head = back;
    m_rot = maxAngle();
    
    if (m_isGrowing)
    {
        m_isGrowing = false;
    }
    else
    {
        m_tail.back()->remSnaky(this);
        m_tail.pop_back();
    }
}

void Snaky::startMovingAnimation()
{
    if (m_isMovingAnimation) return;
    m_isMovingAnimation = true;
    
    m_rot = maxAngle();
}

void Snaky::finishMovingAnimation()
{
    if (!m_isMovingAnimation) return;
    m_isMovingAnimation = false;
}



void Snaky::repeatTrajectory()
{
    repeatTrajectory(m_trajectory);
}

void Snaky::setTrajectory(Tile *tile)
{
    m_trajectory.clear();
    m_trajectory.push_front(tile);
}

void Snaky::setTrajectoryPoint(glm::ivec2 p)
{
    glm::ivec2 lastRelTrajectoryPoint = m_relTargetPoint;
    
    std::list<Tile *> trajectory;
    m_relTargetPoint = p - m_head->getFieldPos();
    repeatTrajectory(trajectory);
    if (trajectory.empty())
    {
        m_relTargetPoint = lastRelTrajectoryPoint;
    }
    else
    {
        // DLT: debug output
        Log::inst()->message("New target: "
                    + std::to_string(p.x)
                    + " | "
                    + std::to_string(p.y)
                    );
        Log::inst()->printLog(1);
        m_trajectory.clear();
        std::copy(trajectory.begin(), trajectory.end(), m_trajectory.begin());
    }
}



void Snaky::die()
{
    for (auto t : m_tail)
    {
        t->remSnaky(this);
        FoodCreator::inst()->addFood(t);
    }
    m_head->remSnaky(this);
    FoodCreator::inst()->addFood(m_head);
}



// private:



void Snaky::makeTrajectory(
        std::list<Tile *> &trajectory, float tanAngle,
        bool mirroredX, bool mirroredY
                           )
{
    trajectory.clear();
    
    int kx = mirroredX ? -1 : 1;
    int ky = mirroredY ? -1 : 1;
    
    int shiftX = m_head->getFieldPos().x;
    int shiftY = m_head->getFieldPos().y;
    
    int x = 0;
    int y = 0;
    Tile *next = nullptr;
    const glm::ivec2 targetPoint = m_relTargetPoint + m_head->getFieldPos();
    
    if (tanAngle <= 1.0f)
    {
        // TODO: think about how to cram it into one cycle and make it easier
        for (int i = 1; !(x == targetPoint.x && y == targetPoint.y); ++i)
        {
            x = kx * i + shiftX;
            y = ky * std::round(tanAngle * i) + shiftY;
            next = m_field->getTile(x, y);
            if (next == nullptr || next->haveSnaky(this)) return;
            
            Tile *prev;
            if (!trajectory.empty())
                prev = trajectory.front();
            else
                prev = m_head;
            
            if (!m_field->canMoveDirectlyTo(prev, next))
            {
                Tile *bridge;
                if ((!next->isInverted() && !mirroredY)
                        || (next->isInverted() && mirroredY))
                    bridge = m_field->getTile(x, y - 1*ky);
                else
                    bridge = m_field->getTile(x - 1*kx, y);
                if (bridge == nullptr || bridge->haveSnaky(this)) return;
                trajectory.push_front(bridge);
            }
            
            trajectory.push_front(next);
        }
    }
    else
    {
        for (int i = 1; !(x == targetPoint.x && y == targetPoint.y); ++i)
        {
            x = kx * std::round(i / tanAngle) + shiftX;
            y = ky * i + shiftY;
            next = m_field->getTile(x, y);
            if (next == nullptr || next->haveSnaky(this)) return;
            
            Tile *prev;
            if (!trajectory.empty())
                prev = trajectory.front();
            else
                prev = m_head;
            
            if (!m_field->canMoveDirectlyTo(prev, next))
            {
                Tile *bridge;
                if  (next->getFieldPos().y - prev->getFieldPos().y == 1*ky
                     && next->getFieldPos().x == prev->getFieldPos().x
                     && ((next->isInverted() && !mirroredY)
                         || (!next->isInverted() && mirroredY)))
                {
                    // if you want to teach a snake to bypass =
                    // single obstacles - add here
                    bridge = m_field->getTile(x + 1*kx, y - 1*ky);
                    if (bridge == nullptr || bridge->haveSnaky(this)) return;
                    trajectory.push_front(bridge);
                    bridge = m_field->getTile(x + 1*kx, y);
                }
                else if ((!next->isInverted() && !mirroredY)
                         || (next->isInverted() && mirroredY))
                    bridge = m_field->getTile(x, y - 1*ky);
                else
                    bridge = m_field->getTile(x - 1*kx, y);
                if (bridge == nullptr || bridge->haveSnaky(this)) return;
                trajectory.push_front(bridge);
            }
            
            trajectory.push_front(next);
        }
    }
}

void Snaky::repeatTrajectory(std::list<Tile *> &trajectory)
{
    if (trajectory.empty())
    {
        // DLT:
        // m_targetPoint = glm::ivec2(rand() % 49 + 1, rand() % 24 + 1);
        // DLT: debug output
        /*const glm::ivec2 targetPoint = m_relTargetPoint + m_head->getFieldPos();
        Log::inst()->message("New target: "
                    + std::to_string(targetPoint.x)
                    + " | "
                    + std::to_string(targetPoint.y)
                    );
        Log::inst()->printLog(1);*/
        
        int x = m_relTargetPoint.x;
        int y = m_relTargetPoint.y;
        float tanAngle = y / (x * 1.0f);
        bool xIsN = x < 0;
        bool yIsN = y < 0.0f;
        makeTrajectory(
                    trajectory, tanAngle < 0 ? -tanAngle : tanAngle, xIsN, yIsN
                       );
    }
}



void Snaky::drawPiece(Tile *location)
{
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(location->getPos()));
    m_model = glm::rotate(
                m_model,
                location->isInverted() ? glm::pi<float>() : 0.0f,
                glm::vec3(0.0f, 0.0f, 1.0f)
                          );
    
    glUniformMatrix4fv(m_modelMatLoc, 1, GL_FALSE, &m_model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Snaky::drawMovingPiece(Tile *previous, Tile *location, float rot)
{
    //m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(location->getPos()));
    
    glm::vec2 axis;
    glm::vec3 shift(0.0f);
    const float offset = Field::distance() / 2.0f;
    const float d = std::sqrt(3.0f) / 8.0f + offset;
    
    if (!location->isInverted())
    {
        if (previous == m_field->getTileByDir(location, Direction::LEFT))
        {
            axis = location->getPointUp(0.0) - location->getPointLeft(0.0);
            shift.x = (std::sqrt(3.0f) / 2.0f) * d;
            shift.y = -d / 2.0f;
        }
        else if (previous == m_field->getTileByDir(location, Direction::RIGHT))
        {
            axis = location->getPointUp(0.0) - location->getPointRight(0.0);
            shift.x = -(std::sqrt(3.0f) / 2.0f) * d;
            shift.y = -d / 2.0f;
        }
        else if (previous == m_field->getTileByDir(location, Direction::DOWN))
        {
            axis = location->getPointLeft(0.0) - location->getPointRight(0.0);
            shift.y = 2 * d - offset;
        }
    }
    else
    {
        if (previous == m_field->getTileByDir(location, Direction::LEFT))
        {
            axis = location->getPointUp(0.0) - location->getPointRight(0.0);
            shift.x = (std::sqrt(3.0f) / 2.0f) * d;
            shift.y = d / 2.0f;
        }
        else if (previous == m_field->getTileByDir(location, Direction::RIGHT))
        {
            axis = location->getPointUp(0.0) - location->getPointLeft(0.0);
            shift.x = -(std::sqrt(3.0f) / 2.0f) * d;
            shift.y = d / 2.0f;
        }
        else if (previous == m_field->getTileByDir(location, Direction::UP))
        {
            axis = location->getPointLeft(0.0) - location->getPointRight(0.0);
            shift.y = -(2 * d - offset);
        }
    }
    
    m_model = glm::translate(
                m_model,
                -shift
                );
    m_model = glm::rotate(
                m_model,
                rot,
                glm::vec3(axis.x, axis.y, 0.0f)
                );
    m_model = glm::translate(
                m_model,
                shift
                );
    m_model = glm::rotate(
                m_model,
                location->isInverted() ? glm::pi<float>() : 0.0f,
                glm::vec3(0.0f, 0.0f, 1.0f)
                          );
    
    glUniformMatrix4fv(m_modelMatLoc, 1, GL_FALSE, &m_model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



void Snaky::makeModel()
{
    if (m_modelIsDone) return;
    m_modelIsDone = true;
    
    m_modelsVerticesCount = 9;
    m_modelsVertices = new GLfloat[m_modelsVerticesCount]
    {
        0.5f, -topPointY(), 0.0f,
        -0.5f, -topPointY(), 0.0f,
        0.0f, topPointY(), 0.0f
    };
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
                GL_ARRAY_BUFFER, m_modelsVerticesCount * sizeof(GLfloat),
                m_modelsVertices, GL_STATIC_DRAW
                );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE,
                3 * sizeof(GLfloat),
                static_cast<GLvoid *>(0)
                );
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    Shader vertShader(GL_VERTEX_SHADER, "snakyShader.vert");
    Shader fragShader(GL_FRAGMENT_SHADER, "snakyShader.frag");
    m_shaderProgram = new ShaderProgram(vertShader, fragShader);
    m_modelMatLoc = m_shaderProgram->getUniformLocation("model");
    m_viewMatLoc = m_shaderProgram->getUniformLocation("view");
    m_projMatLoc = m_shaderProgram->getUniformLocation("proj");
    m_colorLoc = m_shaderProgram->getUniformLocation("inColor");
}
