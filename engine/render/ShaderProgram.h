#ifndef H_SHADER_PROGRAM
#define H_SHADER_PROGRAM



#include "Shader.h"



class ShaderProgram
{

public:
    ShaderProgram(Shader vertex, Shader fragment);
    ~ShaderProgram();
    void use();
    
private:
    GLuint m_program;
};





#endif // H_SHADER_PROGRAM
