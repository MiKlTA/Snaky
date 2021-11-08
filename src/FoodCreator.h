#ifndef H_FOOD_CREATOR
#define H_FOOD_CREATOR



#include <random>
#include <algorithm>



#include "engine/handle/Timer.h"
#include "src/Field.h"



class FoodCreator : public Timer
{
    
public:
    static FoodCreator * inst();
    
    void onTick(double curTime) override; 
    
    void setNormalFoodCount(int nfc) {m_normalFoodCount = nfc;};
    void setMaximumFoodCount(int mfc) {m_maximumFoodCount = mfc;};
    
    void addFood(Tile *tile);
    void decFoodCount();
    
    void bindField(Field *field);
    
private:
    static FoodCreator *m_instance;
    FoodCreator();
    
    Field *m_field;
    
    int m_normalFoodCount;
    int m_maximumFoodCount;
    int m_foodCount;
    int m_passing;
    
    void createFood();
    
    static float foodSpawningTime() {return 1.0;};
};


#endif // H_FOOD_CREATOR
