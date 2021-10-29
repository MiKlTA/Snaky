#include "Tile.h"



bool Tile::m_modelIsDone = false;
GLfloat *Tile::m_modelsVertices = nullptr;
unsigned int Tile::m_modelsVerticesCount = 0;
GLuint Tile::m_VBO = 0;
GLuint Tile::m_VAO = 0;
ShaderProgram *Tile::m_shaderProgram = nullptr;
GLuint Tile::m_modelMatLoc = 0;
GLuint Tile::m_viewMatLoc = 0;
GLuint Tile::m_projMatLoc = 0;



Tile::Tile(
        Render *render, TileType tt,
        const glm::vec3 rot
        )
    : RenderingObject(render),
      m_tileType(tt),
      m_pos(0.0f, 0.0f, 1.0f),
      m_rot(rot),
      m_scale(glm::vec3(1.0f)),
      m_model(1.0f)
{
    makeModel();
}



void Tile::draw(const glm::mat4 &view, const glm::mat4 &proj)
{
    glBindVertexArray(m_VAO);
    m_shaderProgram->use();
    glUniformMatrix4fv(m_modelMatLoc, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_viewMatLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projMatLoc, 1, GL_FALSE, &proj[0][0]);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}



// private



void Tile::makeModel()
{
    if (m_modelIsDone) return;
    m_modelIsDone = true;
    
    m_modelsVerticesCount = 9;
    m_modelsVertices = new GLfloat[m_modelsVerticesCount]
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
                GL_ARRAY_BUFFER, sizeof(m_modelsVertices),
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
}
