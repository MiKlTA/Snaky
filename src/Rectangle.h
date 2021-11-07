#ifndef H_RECTANGLE
#define H_RECTANGLE



#include <set>
#include <math.h>

#include "../engine/render/Render.h"
#include "../engine/render/Shader.h"
#include "../engine/render/ShaderProgram.h"

#include "GLM/vec2.hpp"
#include "GLM/matrix.hpp"



class Rectangle : public RenderingObject
{
public:
    Rectangle(
            RenderingObject *parent, glm::vec4 color,
            glm::vec2 pos, glm::vec2 size
              );
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    void stretchBetween(glm::vec2 point1, glm::vec2 point2, float width);
    
private:
    glm::vec3 m_pos;
    float m_rot;
    glm::vec3 m_scale;
    const glm::vec4 m_color;
    glm::mat4 m_model;
    
    static bool m_modelIsDone;
    static GLfloat *m_modelsVertices;
    static unsigned int m_modelsVerticesCount;
    static GLuint *m_modelsIndices;
    static unsigned int m_indicesCount;
    static GLuint m_VBO, m_VAO, m_EBO;
    static ShaderProgram *m_shaderProgram;
    static GLuint m_modelMatLoc, m_viewMatLoc, m_projMatLoc, m_colorLoc;
    
    
    
    static void makeModel();
    void updModelMat();
};



#endif // H_RECTANGLE
