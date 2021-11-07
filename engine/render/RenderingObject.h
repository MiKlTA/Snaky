#ifndef H_RENDERING_OBJECT
#define H_RENDERING_OBJECT



#include <algorithm>
#include <vector>

#include "GLM/matrix.hpp"



class RenderingObject
{

public:
    RenderingObject();
    RenderingObject(RenderingObject *parent);
    virtual ~RenderingObject();
    
    void addRenderingObject(RenderingObject *rObj);
    void removeRenderingObject(RenderingObject *rObj);
    
    virtual void draw(const glm::mat4 &view, const glm::mat4 &proj) = 0;
    void recursiveDraw(const glm::mat4 &view, const glm::mat4 &proj);
    
    void hide() {m_visible = false;};
    void show() {m_visible = true;};
    
private:
    RenderingObject *m_parent;
    std::vector<RenderingObject *> m_renderingObjects;
    
    bool m_visible;
};







#endif // H_RENDERING_OBJECT
