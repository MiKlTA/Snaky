#ifndef H_SHADER_PROGRAM
#define H_SHADER_PROGRAM



#include "Shader.h"

#include "../Log.h"




class ShaderProgram
{

public:
    ShaderProgram(Shader vertex, Shader fragment);
    ~ShaderProgram();
    void use();
    GLuint getUniformLocation(const char *name);
    
private:
    GLuint m_program;
};





#endif // H_SHADER_PROGRAM
