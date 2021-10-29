#ifndef H_TILE
#define H_TILE



#include <set>

#include "../engine/render/RenderingObject.h"
#include "../engine/render/Shader.h"
#include "../engine/render/ShaderProgram.h"

#include "GLM/vec2.hpp"
#include "GLM/matrix.hpp"



class Snaky;



class Tile : public RenderingObject
{
public:
    enum class TileType
    {
        VOID,
        SOLID,
        FOOD
    };
    
    Tile(
            Render *render, TileType tt,
            const glm::vec3 rot
         );
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    
    
    void addFood() {m_tileType = TileType::FOOD;};
    void eatFood() {m_tileType = TileType::SOLID;};
    const std::set<Snaky *> & getSnaky() {return m_snaky;};
    void addSnaky(Snaky *snaky) {m_snaky.insert(snaky);};
    void remSnaky(Snaky *snaky) {m_snaky.erase(snaky);};
    
    void setPos(); // TODO
    
private:
    TileType m_tileType;
    std::set<Snaky *> m_snaky;
    
    glm::vec3 m_pos;
    const glm::vec3 m_rot;
    const glm::vec3 m_scale;
    glm::mat4 m_model;
    
    
    
    static bool m_modelIsDone;
    static GLfloat *m_modelsVertices;
    static unsigned int m_modelsVerticesCount;
    static GLuint m_VBO, m_VAO;
    static ShaderProgram *m_shaderProgram;
    static GLuint m_modelMatLoc, m_viewMatLoc, m_projMatLoc;
    
    
    
    static void makeModel();
};



#endif // H_TILE
