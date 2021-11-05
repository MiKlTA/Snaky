#ifndef H_TILE
#define H_TILE



#include <set>

#include "../engine/render/RenderingObject.h"
#include "../engine/render/Shader.h"
#include "../engine/render/ShaderProgram.h"

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
            Render *render, TileType tt, glm::ivec2 pos,
            bool isPeaceful, bool isInverted
         );
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    void addFood() {m_tileType = TileType::FOOD;};
    void eatFood() {m_tileType = TileType::VOID;};
    bool haveFood() {return m_tileType == TileType::FOOD;};
    bool isSolid() {return m_tileType == TileType::SOLID;};
    
    void addSnaky(Snaky *snaky) {m_snaky.insert(snaky);};
    void remSnaky(Snaky *snaky) {m_snaky.erase(snaky);};
    bool haveSnaky(Snaky *snaky);
    bool haveSnaky();
    bool isSnakyUnique();
    
    // returns the position of the triangle point
    // with an offset from the center d
    glm::vec2 getPointUp(float d);
    glm::vec2 getPointLeft(float d);
    glm::vec2 getPointRight(float d);
    
    const glm::vec3 & getPos() const {return m_pos;};
    const glm::ivec2 & getFieldPos() const {return m_fieldPos;};
    bool isPeaceful() const {return m_isPeaceful;};
    bool isInverted() const {return m_isInverted;};
    
private:
    TileType m_tileType;
    bool m_isPeaceful;
    std::set<Snaky *> m_snaky;
    glm::ivec2 m_fieldPos;
    bool m_isInverted;
    
    glm::vec3 m_pos;
    const float m_rot;
    const glm::vec3 m_scale;
    glm::mat4 m_model;
    glm::vec4 m_color;
    
    const glm::vec3 m_foodScale;
    glm::mat4 m_foodModel;
    const glm::vec4 m_foodColor;
    
    static bool m_modelIsDone;
    static GLfloat *m_modelsVertices;
    static unsigned int m_modelsVerticesCount;
    static GLuint m_VBO, m_VAO;
    static ShaderProgram *m_shaderProgram;
    static GLuint m_modelMatLoc, m_viewMatLoc, m_projMatLoc, m_colorLoc;
    
    static void makeModel();
    void updModelMat();
    
    static float topPointY() {return std::sqrt(3.0f)/4.0f;};
};



#endif // H_TILE
