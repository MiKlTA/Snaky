#include "Tile.h"

#include "Field.h"



bool Tile::m_modelIsDone = false;
GLfloat *Tile::m_modelsVertices = nullptr;
unsigned int Tile::m_modelsVerticesCount = 0;
GLuint Tile::m_VBO = 0;
GLuint Tile::m_VAO = 0;
ShaderProgram *Tile::m_shaderProgram = nullptr;
GLuint Tile::m_modelMatLoc = 0;
GLuint Tile::m_viewMatLoc = 0;
GLuint Tile::m_projMatLoc = 0;
GLuint Tile::m_colorLoc = 0;



Tile::Tile(Render *render, TileType tt, glm::ivec2 pos, bool isInverted)
    : RenderingObject(render),
      m_tileType(tt),
      m_snaky(),
      m_fieldPos(pos),
      m_isInverted(isInverted),
      m_pos(Field::getTilePos(pos.x, pos.y)),
      m_rot(glm::pi<float>() * isInverted),
      m_scale(1.0f),
      m_model(1.0f)
{
    makeModel();
    updModelMat();
    
    switch (tt)
    {
    case TileType::VOID:
        m_color = glm::vec4(1.0f, 0.95f, 0.83f, 1.0f);
        break;
    case TileType::SOLID:
        m_color = glm::vec4(0.75f, 0.7f, 0.6f, 1.0f);
        break;
    case TileType::FOOD:
        
        break;
    }
}



void Tile::draw(const glm::mat4 &view, const glm::mat4 &proj)
{
    glBindVertexArray(m_VAO);
    m_shaderProgram->use();
    glUniformMatrix4fv(m_modelMatLoc, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_viewMatLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projMatLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform4fv(m_colorLoc, 1, &m_color[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



glm::vec2 Tile::getPointUp(float d)
{
    return glm::vec2(m_pos.x, m_pos.y + topPointY() + d);
}

glm::vec2 Tile::getPointLeft(float d)
{
    return glm::vec2(
                m_pos.x - 0.5f - (std::sqrt(3.0f) / 2.0f) * d,
                m_pos.y - topPointY() - 0.5 * d
                     );
}

glm::vec2 Tile::getPointRight(float d)
{
    return glm::vec2(
                m_pos.x + 0.5f + (std::sqrt(3.0f) / 2.0f) * d,
                m_pos.y - topPointY() - 0.5 * d
                );
}



// private



void Tile::makeModel()
{
    if (m_modelIsDone) return;
    m_modelIsDone = true;
    
    m_modelsVerticesCount = 9;
    m_modelsVertices = new GLfloat[m_modelsVerticesCount]
    {
        -0.5f, -topPointY(), 0.0f,
        0.5f, -topPointY(), 0.0f,
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
    
    Shader vertShader(GL_VERTEX_SHADER, "shader.vert");
    Shader fragShader(GL_FRAGMENT_SHADER, "shader.frag");
    m_shaderProgram = new ShaderProgram(vertShader, fragShader);
    m_modelMatLoc = m_shaderProgram->getUniformLocation("model");
    m_viewMatLoc = m_shaderProgram->getUniformLocation("view");
    m_projMatLoc = m_shaderProgram->getUniformLocation("proj");
    m_colorLoc = m_shaderProgram->getUniformLocation("inColor");
}



void Tile::updModelMat()
{
    m_model = glm::translate(glm::mat4(1.0f), m_pos);
    m_model = glm::rotate(m_model, m_rot, glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::scale(m_model, m_scale);
}
