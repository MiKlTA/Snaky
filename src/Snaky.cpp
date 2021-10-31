#include "Snaky.h"

#include "Field.h"



Snaky::Snaky(Render *render, Tile *head, Tile *tail, glm::vec4 color)
    : RenderingObject(render),
      Timer(movingTime()),
      FastTimer(movingTime() / (1.0 * stageOfMoving())),
      m_head(head),
      m_tail(),
      m_isMoving(false),
      m_targetTile(nullptr),
      m_model(1.0f),
      m_color(color)
{
    m_tail.push_back(tail);
}



void Snaky::draw(const glm::mat4 &view, const glm::mat4 &proj)
{
    glBindVertexArray(m_VAO);
    m_shaderProgram->use();
    glUniformMatrix4fv(m_viewMatLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projMatLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform4fv(m_colorLoc, 1, &m_color[0]);
    
    
    for (auto t : m_tail)
    {
    }
}



void Snaky::onTick()
{
    // TODO: Moving, eating and dying
}

void Snaky::onFastTick()
{
    // TODO: calc head moving stage
}



void Snaky::setDirection(glm::vec2 point)
{
    // TODO: think about how to do it
}

void Snaky::startMoveNow(Tile *target)
{
    m_targetTile = target;
}



// private:



void Snaky::finishMoving()
{
    if (!m_isMoving) return;
    m_isMoving = false;
}

void Snaky::drawPiece(Tile *location)
{
    m_model = 
    
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
