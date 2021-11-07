#include "Rectangle.h"



bool Rectangle::m_modelIsDone = false;
GLfloat *Rectangle::m_modelsVertices = nullptr;
unsigned int Rectangle::m_modelsVerticesCount = 0;
GLuint *Rectangle::m_modelsIndices = nullptr;
unsigned int Rectangle::m_indicesCount = 0;
GLuint Rectangle::m_VBO = 0;
GLuint Rectangle::m_VAO = 0;
GLuint Rectangle::m_EBO = 0;
ShaderProgram *Rectangle::m_shaderProgram = nullptr;
GLuint Rectangle::m_modelMatLoc = 0;
GLuint Rectangle::m_viewMatLoc = 0;
GLuint Rectangle::m_projMatLoc = 0;
GLuint Rectangle::m_colorLoc = 0;



Rectangle::Rectangle(
        RenderingObject *parent, glm::vec4 color, glm::vec2 pos, glm::vec2 size
                     )
    : RenderingObject(parent),
      m_pos(pos.x, pos.y, 0.0f),
      m_rot(0.0f),
      m_scale(size.x, size.y, 1.0f),
      m_color(color),
      m_model(1.0f)
{
    makeModel();
    updModelMat();
}



void Rectangle::draw(const glm::mat4 &view, const glm::mat4 &proj)
{
    glBindVertexArray(m_VAO);
    m_shaderProgram->use();
    glUniformMatrix4fv(m_modelMatLoc, 1, GL_FALSE, &m_model[0][0]);
    glUniformMatrix4fv(m_viewMatLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(m_projMatLoc, 1, GL_FALSE, &proj[0][0]);
    glUniform4fv(m_colorLoc, 1, &m_color[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}



void Rectangle::stretchBetween(glm::vec2 point1, glm::vec2 point2, float width)
{
    const glm::vec2 forming = point2 - point1;
    const float length = glm::length(forming);
    const float angle = (forming.x == 0 ? glm::pi<float>() / 2.0f
                  : std::atan(forming.y / forming.x)
                                          );
    m_pos.x = (point1.x + point2.x) / 2.0f;
    m_pos.y = (point1.y + point2.y) / 2.0f;
    m_rot = angle;
    m_scale = glm::vec3(length, width, 1.0f);
    
    updModelMat();
}



// private



void Rectangle::makeModel()
{
    if (m_modelIsDone) return;
    m_modelIsDone = true;
    
    m_modelsVerticesCount = 12;
    m_modelsVertices = new GLfloat[m_modelsVerticesCount]
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    
    m_indicesCount = 6;
    m_modelsIndices = new GLuint[m_indicesCount]
    {
        0, 1, 2,
        1, 2, 3
    };
    
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
                GL_ARRAY_BUFFER, m_modelsVerticesCount * sizeof(GLfloat),
                m_modelsVertices, GL_STATIC_DRAW
                );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(
                GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(GLuint),
                m_modelsIndices, GL_STATIC_DRAW
                 );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE,
                3 * sizeof(GLfloat),
                static_cast<GLvoid *>(0)
                );
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    
    Shader vertShader(GL_VERTEX_SHADER, "rectShader.vert");
    Shader fragShader(GL_FRAGMENT_SHADER, "rectShader.frag");
    m_shaderProgram = new ShaderProgram(vertShader, fragShader);
    m_modelMatLoc = m_shaderProgram->getUniformLocation("model");
    m_viewMatLoc = m_shaderProgram->getUniformLocation("view");
    m_projMatLoc = m_shaderProgram->getUniformLocation("proj");
    m_colorLoc = m_shaderProgram->getUniformLocation("inColor");
}



void Rectangle::updModelMat()
{
    m_model = glm::translate(glm::mat4(1.0f), m_pos);
    m_model = glm::rotate(m_model, m_rot, glm::vec3(0.0f, 0.0f, 1.0f));
    m_model = glm::scale(m_model, m_scale);
}
