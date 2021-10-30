#include "WindowActiveListener.h"

#include "Window.h"



WindowActiveListener::WindowActiveListener()
{
    Window::inst()->addWindowActiveListener(this);
}

WindowActiveListener::~WindowActiveListener()
{
    Window::inst()->revWindowActiveListener(this);
}
