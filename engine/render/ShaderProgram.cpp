#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(Shader vertex, Shader fragment)
{
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex.getShader());
    glAttachShader(m_program, fragment.getShader());
    glLinkProgram(m_program);
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_program);
}



void ShaderProgram::use()
{
    glUseProgram(m_program);
}
