#include "Joystick.h"

void initJoystick(void)
{
    pinMode(JOYSTICK_Z, INPUT_PULLUP);
}

int joystickStatus(int xValue, int yValue)
{
    int status = -1;

    if(xValue < JOYSTICK_UP)
        status = UP;
    else if(xValue > JOYSTICK_DOWN)
        status = DOWN;
    
    if(yValue < JOYSTICK_RIGHT)
        status = RIGHT;
    else if(yValue > JOYSTICK_LEFT)
        status = LEFT;

    return status;
}
