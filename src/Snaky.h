#ifndef H_SNAKY
#define H_SNAKY



#include <list>

#include "../engine/render/RenderingObject.h"
#include "../engine/handle/Timer.h"
#include "../engine/etc/Direction.h"

#include "Tile.h"
#include "Field.h"




class Snaky : public RenderingObject, public Timer
{
    
public:
    Snaky(
            Render *render, Field *field, Tile *head,
            Tile **tail, int tailLength,
            glm::vec4 color
          );
    ~Snaky();
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    void onTick() override;
    
    Tile * getHead() {return m_head;};
    Tile * getNextTile();
    
    void move();
    void startMovingAnimation();
    void finishMovingAnimation();
    void updateTrajectory();
    void setTrajectory(Tile *tile);
    void setTrajectoryPoint(glm::ivec2 p);
    
    void grow() {m_isGrowing = true;};
    void die();
    
    static double movingTime() {return 0.3;};
    
private:
    Field *m_field;
    Tile *m_head;
    std::list<Tile *> m_tail;
    
    bool m_isGrowing;
    bool m_isMovingAnimation;
    std::list<Tile *> m_trajectory;
    // how much is the target point shifted relative to the head
    glm::ivec2 m_relTargetPoint;
    
    float m_rot;
    
    void makeTrajectory(float tanAngle, bool mirroredX, bool mirroredY);
    void drawPiece(Tile *location);
    void drawMovingPiece(Tile *previous, Tile *location, float rot);
    
    glm::mat4 m_model;
    glm::vec4 m_color;
    
    static bool m_modelIsDone;
    static GLfloat *m_modelsVertices;
    static unsigned int m_modelsVerticesCount;
    static GLuint m_VBO, m_VAO;
    static ShaderProgram *m_shaderProgram;
    static GLuint m_modelMatLoc, m_viewMatLoc, m_projMatLoc;
    static GLuint m_colorLoc;
    static GLuint m_centrePosLoc;
    
    static void makeModel();
    
    static float topPointY() {return std::sqrt(3.0f)/4.0f;};
    static int stageOfMoving() {return 30;};
    static float maxAngle() {return glm::pi<float>();};
    static float deltaAngle() {return maxAngle()/(stageOfMoving() * 1.0f);};
};



#endif // H_SNAKY
