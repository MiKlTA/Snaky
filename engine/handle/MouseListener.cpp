#include "MouseListener.h"

#include "Mouse.h"



MouseListener::MouseListener()
{
    Mouse::inst()->addListener(this);
}

MouseListener::~MouseListener()
{
    Mouse::inst()->remListener(this);
}
