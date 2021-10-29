#ifndef H_MOUSE_LISTENER
#define H_MOUSE_LISTENER



class MouseListener
{
    
public:
    MouseListener();
    virtual ~MouseListener();
    
    virtual void onMouseLeftClick() {};
    virtual void onMouseRightClick() {};
    
    virtual void onMouseMove(double x, double y) {};
};



#endif // H_MOUSE_LISTENER
