#include "Snaky.h"

#include "Field.h"



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
      m_isMoving(false),
      m_direction(0.0f),
      m_tilesPassed(0),
      m_startPoint(head->getFieldPos()),
      m_movingStage(0.0f),
      m_model(1.0f),
      m_color(color)
{
    for (int i = 0; i < tailLength; ++i)
    {
        m_tail.push_back(tail[i]);
    }
    
    makeModel();
    
    m_startPoint = m_head->getFieldPos();
}

Snaky::~Snaky()
{
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
    
    drawPiece(m_head);
    for (auto t : m_tail)
    {
        drawPiece(t);
    }
}



void Snaky::onTick()
{
    // TODO: calc moving
    
}



void Snaky::changeDirection(float dir)
{
    m_startPoint = m_head->getFieldPos();
    m_direction = dir;
    m_tilesPassed = 0;
}

void Snaky::startMoveNow()
{
    if (m_isMoving) return;
    
    Tile *next = nextTile();
    if (next == nullptr) return;
    m_tilesPassed++;
    
    next->addSnaky(this);
    m_tail.push_front(m_head);
    m_head = next;
    
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

void Snaky::finishMoving()
{
    if (!m_isMoving) return;
    
    m_isMoving = false;
    m_movingStage = 0.0f;
    m_tilesPassed = 0;
    m_startPoint = glm::ivec2(0, 0);
}



Tile * Snaky::nextTile()
{
    return m_field->getTileOnLine(
                m_startPoint, m_direction, m_tilesPassed + 1
                );
}



// private:



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

void Snaky::drawMovingPiece(Tile *location, float stage)
{
    // TODO:
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
