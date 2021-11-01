#ifndef H_SNAKY
#define H_SNAKY



#include <list>

#include "../engine/render/RenderingObject.h"
#include "../engine/handle/Timer.h"
#include "../engine/etc/Direction.h"

#include "Tile.h"



class FastTimer : public Timer
{
    
public:
    FastTimer(double delay) : Timer(delay) {};
    
    virtual void onFastTick() = 0;
    void onTick() override {onFastTick();};
};



class Snaky : public RenderingObject, public Timer, public FastTimer
{
    
public:
    Snaky(Render *render, Tile *head, Tile *tail, glm::vec4 color);
    
    void draw(const glm::mat4 &view, const glm::mat4 &proj) override;
    
    void onTick() override;
    void onFastTick() override;
    
    Tile * getHead() {return m_head;};
    
    void setDirection(glm::vec2 point);
    void startMoveNow(Tile *target);
    
private:
    Tile *m_head;
    std::list<Tile *> m_tail;
    
    bool m_isMoving;
    Tile *m_targetTile;
    
    void finishMoving();
    void drawPiece(Tile *location);
    
    glm::mat4 m_model;
    glm::vec4 m_color;
    
//    static bool m_modelIsDone;
//    static GLfloat *m_modelsVertices;
//    static unsigned int m_modelsVerticesCount;
//    static GLuint m_VBO, m_VAO;
//    static ShaderProgram *m_shaderProgram;
//    static GLuint m_modelMatLoc, m_viewMatLoc, m_projMatLoc;
//    static GLuint m_colorLoc;
//    static GLuint m_centrePosLoc;
    
    static void makeModel();
    
    static float topPointY() {return std::sqrt(3.0f)/4.0f;};
    static double movingTime() {return 2.0;};
    static int stageOfMoving() {return 20;};
};



#endif // H_SNAKY
