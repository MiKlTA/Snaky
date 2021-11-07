#ifndef H_SNAKY_CREATOR
#define H_SNAKY_CREATOR



#include <random>

#include "Snaky.h"
#include "Field.h"
#include "engine/render/Render.h"



class SnakyCreator
{
    
public:
    static SnakyCreator * inst();
    
    void setField(Field *field) {m_field = field;};
    void setSpawnArea(glm::ivec2 p1, glm::ivec2 p2);
    
    void build();
    Snaky * getProduct();
    
    static int initialLength() {return 3;};
    
private:
    static SnakyCreator *m_instance;
    SnakyCreator();
    
    Snaky *m_product;
    
    Field *m_field;
    glm::ivec2 m_sAPoint1;
    glm::ivec2 m_sAPoint2;
    
    static int safeDistance() {return 3;};
};



#endif // H_SNAKY_CREATOR
