#ifndef H_SHADER
#define H_SHADER



#include <string>
#include <fstream>

#include "engine/gl.h"

#include "../Log.h"



class Shader
{

public:
    Shader(GLuint shaderType, std::string fileName);
    Shader(GLuint shaderType, const char *shaderCode, unsigned int size);
    ~Shader();
    
    GLuint getShader() const {return m_shader;};
    
private:
    GLuint m_shader;
    
    void init(GLuint shaderType, const char *shaderCode, int size);
};





#endif // H_SHADER
