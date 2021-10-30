#ifndef H_WINDOW_ACTIVE_LISTENER
#define H_WINDOW_ACTIVE_LISTENER



class WindowActiveListener
{

public:
    WindowActiveListener();
    virtual ~WindowActiveListener();
    
    virtual void onWindowResize(int w, int h) = 0;
};



#endif // H_WINDOW_ACTIVE_LISTENER
