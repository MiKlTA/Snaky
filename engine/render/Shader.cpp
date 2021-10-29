#include "Shader.h"

#include "../Log.h"



Shader::Shader(GLuint shaderType, std::string fileName)
{
    std::ifstream shaderFile(fileName, std::ios::binary);
    shaderFile.seekg(0, std::ios::end);
    unsigned int fileSize = shaderFile.tellg();
    shaderFile.seekg(0, std::ios::beg);
    fileSize++;
    char *shaderCode = new char[fileSize];
    shaderFile.read(shaderCode, fileSize);
    shaderCode[fileSize - 1] = '\0';
    
    init(shaderType, shaderCode, fileSize);
}

Shader::Shader(GLuint shaderType, const char *shaderCode, unsigned int size)
{
    init(shaderType, shaderCode, size);
}

Shader::~Shader()
{
    glDeleteShader(m_shader);
}



// private



void Shader::init(GLuint shaderType, const char *shaderCode, int size)
{
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, &shaderCode, &size);
    glCompileShader(m_shader);
    
    GLint isCompiled = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);
        
        char *logInfo = new char[length];
        glGetShaderInfoLog(m_shader, length, &length, logInfo);
        
        Log::inst()->error("Shader isn't compiled! Error output:\n");
        Log::inst()->error(std::string(logInfo, length));
        
        delete[] logInfo;
    }
}
