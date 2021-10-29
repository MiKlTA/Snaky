#include "KeyboardListener.h"

#include "Keyboard.h"



KeyboardListener::KeyboardListener()
{
    Keyboard::inst()->addListener(this);
}

KeyboardListener::~KeyboardListener()
{
    Keyboard::inst()->remListener(this);
}
