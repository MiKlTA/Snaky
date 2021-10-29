#include "ShaderProgram.h"



ShaderProgram::ShaderProgram(Shader vertex, Shader fragment)
{
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex.getShader());
    glAttachShader(m_program, fragment.getShader());
    glLinkProgram(m_program);
    
    GLint isLinked = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
        char *logInfo = new char[length];
        
        glGetProgramInfoLog(m_program, length, &length, logInfo);
        
        Log::inst()->error("Shader isn't compiled! Error output:\n");
        Log::inst()->error(std::string(logInfo, length));
        
        delete[] logInfo;
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_program);
}



void ShaderProgram::use()
{
    glUseProgram(m_program);
}

GLuint ShaderProgram::getUniformLocation(const char *name)
{
    return glGetUniformLocation(m_program, name);
}
