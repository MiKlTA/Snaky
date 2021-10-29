#ifndef H_KEYBOARD_LISTENER
#define H_KEYBOARD_LISTENER



class KeyboardListener
{
    
public:
    KeyboardListener();
    virtual ~KeyboardListener();
    
    virtual void onKeyDown(int key) {};
    virtual void onKeyPress(int key) {};
    virtual void onKeyUp(int key) {};
};



#endif // H_KEYBOARD_LISTENER
