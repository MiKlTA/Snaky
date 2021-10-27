#ifndef H_SHADER
#define H_SHADER



#include <string>
#include <fstream>

#include "engine/gl.h"



class Shader
{

public:
    Shader(GLuint shaderType, std::string fileName);
    Shader(GLuint shaderType, const char *shaderCode);
    ~Shader();
    
    GLuint getShader() const {return m_shader;};
    
private:
    GLuint m_shader;
    char *m_shaderCode;
    
    void init(GLuint shaderType, const char *shaderCode);
};





#endif // H_SHADER
