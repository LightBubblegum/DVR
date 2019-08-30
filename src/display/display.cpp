/**
*/

#include <iostream>
#include "display.h"


Display::Display(IDispDriver *specific_lcd) : 
  monitor(specific_lcd)
{
    if(monitor == nullptr)
        throw "NullPointer";
    monitor->init();
}
