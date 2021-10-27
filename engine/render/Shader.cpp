#include "Shader.h"

#include "../Log.h"



Shader::Shader(GLuint shaderType, std::string fileName)
{
    std::fstream shaderFile(fileName);
    shaderFile.seekg(std::ios::end);
    unsigned int fileSize = shaderFile.tellg();
    shaderFile.seekg(std::ios::beg);
    const char *shaderCode = new char[fileSize];
    init(shaderType, shaderCode);
}

Shader::Shader(GLuint shaderType, const char *shaderCode)
{
    init(shaderType, shaderCode);
}

Shader::~Shader()
{
    glDeleteShader(m_shader);
}



// private



void Shader::init(GLuint shaderType, const char *shaderCode)
{
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, &shaderCode, nullptr);
    glCompileShader(m_shader);
}
