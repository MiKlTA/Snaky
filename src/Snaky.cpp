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
      m_targetPoint(0.0f),
      
      m_rot(maxAngle()),
      
      m_model(1.0f),
      m_color(color)
{
    for (int i = 0; i < tailLength; ++i)
    {
        m_tail.push_back(tail[i]);
    }
    
    makeModel();
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
    
    if (m_isMovingAnimation)
        drawMovingPiece(m_head);
    else
        drawPiece(m_head);
    for (auto t : m_tail)
    {
        drawPiece(t);
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
    Log::inst()->message(
                std::to_string(back->getFieldPos().x)
                + " | "
                + std::to_string(back->getFieldPos().y)
                );
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

void Snaky::updateTrajectory()
{
    if (m_trajectory.empty())
    {
        // DLT:
        m_targetPoint = glm::ivec2(rand() % 49 + 1, rand() % 24 + 1);
        Log::inst()->message("New target: "
                    + std::to_string(m_targetPoint.x)
                    + " | "
                    + std::to_string(m_targetPoint.y)
                    );
        Log::inst()->printLog(1);
        
        int x = m_targetPoint.x - m_head->getFieldPos().x;
        int y = m_targetPoint.y - m_head->getFieldPos().y;
        float tanAngle = y / (x * 1.0f);
        bool xIsN = x < 0;
        bool yIsN = y < 0.0f;
        makeTrajectory(tanAngle < 0 ? -tanAngle : tanAngle, xIsN, yIsN);
    }
}



void Snaky::die()
{
    for (auto t : m_tail)
    {
        t->remSnaky(this);
    }
    m_head->remSnaky(this);
}



// private:


void Snaky::makeTrajectory(float tanAngle, bool mirroredX, bool mirroredY)
{
    int kx = mirroredX ? -1 : 1;
    int ky = mirroredY ? -1 : 1;
    
    int shiftX = m_head->getFieldPos().x;
    int shiftY = m_head->getFieldPos().y;
    
    int x = 0;
    int y = 0;
    Tile *next = nullptr;
    
    if (tanAngle <= 1.0f)
    {
        // TODO: think about how to cram it into one cycle and make it easier
        for (int i = 1; !(x == m_targetPoint.x && y == m_targetPoint.y); ++i)
        {
            x = kx * i + shiftX;
            y = ky * std::round(tanAngle * i) + shiftY;
            next = m_field->getTile(x, y);
            if (next == nullptr) return;
            
            Tile *prev;
            if (!m_trajectory.empty())
                prev = m_trajectory.front();
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
                if (bridge == nullptr) return;
                m_trajectory.push_front(bridge);
            }
            
            m_trajectory.push_front(next);
        }
    }
    else
    {
        for (int i = 1; !(x == m_targetPoint.x && y == m_targetPoint.y); ++i)
        {
            x = kx * std::round(i / tanAngle) + shiftX;
            y = ky * i + shiftY;
            next = m_field->getTile(x, y);
            if (next == nullptr) return;
            
            Tile *prev;
            if (!m_trajectory.empty())
                prev = m_trajectory.front();
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
                    if (bridge == nullptr) return;
                    m_trajectory.push_front(bridge);
                    bridge = m_field->getTile(x + 1*kx, y);
                }
                else if ((!next->isInverted() && !mirroredY)
                         || (next->isInverted() && mirroredY))
                    bridge = m_field->getTile(x, y - 1*ky);
                else
                    bridge = m_field->getTile(x - 1*kx, y);
                if (bridge == nullptr) return;
                m_trajectory.push_front(bridge);
            }
            
            m_trajectory.push_front(next);
        }
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

void Snaky::drawMovingPiece(Tile *location)
{
    //m_model = glm::mat4(1.0f);
    m_model = glm::translate(glm::mat4(1.0f), glm::vec3(location->getPos()));
    
    // TODO: FINISH IT!!!!
    
    Tile *prevTile = m_tail.front();
    glm::vec2 axis;
    glm::vec3 shift(0.0f);
    if (!location->isInverted())
    {
        if (m_field->getTileByDir(prevTile, Direction::LEFT))
        {
            axis = location->getPointUp(0.0) - location->getPointLeft(0.0);
            shift.x = (-3.0f) / 8.0f;
            shift.y = Snaky::topPointY() / 2.0f;
        }
        else if (m_field->getTileByDir(prevTile, Direction::RIGHT))
        {
            axis = location->getPointUp(0.0) - location->getPointRight(0.0);
            shift.x = 3.0f / 8.0f;
            shift.y = Snaky::topPointY() / 2.0f;
        }
        else if (m_field->getTileByDir(prevTile, Direction::DOWN))
        {
            axis = location->getPointLeft(0.0) - location->getPointRight(0.0);
            shift.y = Snaky::topPointY() / 2.0f;
        }
    }
    else
    {
        if (m_field->getTileByDir(prevTile, Direction::LEFT))
        {
            axis = location->getPointUp(0.0) - location->getPointLeft(0.0);
            shift.y = 3.0f / 8.0f;
            shift.x = Snaky::topPointY() / 2.0f;
        }
        else if (m_field->getTileByDir(prevTile, Direction::RIGHT))
        {
            axis = location->getPointUp(0.0) - location->getPointRight(0.0);
            shift.y = 3.0f / 8.0f;
            shift.x = - Snaky::topPointY() / 2.0f;
        }
        else if (m_field->getTileByDir(prevTile, Direction::UP))
        {
            axis = location->getPointLeft(0.0) - location->getPointRight(0.0);
            shift.y = Snaky::topPointY() / 2.0f;
        }
    }
    
//    m_model = glm::translate(
//                m_model,
//                -shift
//                );
    m_model = glm::rotate(
                m_model,
                m_rot,
                glm::vec3(axis.x, axis.y, 0.0f)
                );
//    m_model = glm::translate(
//                m_model,
//                shift
//                );
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
        0.0f, topPointY(), 0.0f,
        0.5f, -topPointY(), 0.0f,
        -0.5f, -topPointY(), 0.0f
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
