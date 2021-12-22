#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408TFTLCDLib.h>
#include <SPFD5408_TouchScreen.h>

enum
{
    MAZE = 0,
    TouchCircle,
    FindPitch,
    SelectLED
};

boolean initFlag = true;
int stage = TouchCircle;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    switch(stage)
    {
    case MAZE:
    {
        if(initFlag)
        {
            initJoystick();
            initMazeLCD();
            drawMaze();
            initFlag = false;
        }
        
        maze();
        break;
    }
    case TouchCircle:
    {
        if(initFlag)
        {
            initTouchCircleLCD();
            initFlag = false;
        }

        touchCircle();
        break;
    }
    case FindPitch:
    {
        if(initFlag)
        {
            initFindPitch();
            initFlag = false;
        }

        findPitch();
        break;
    }
    case SelectLED:
    {
        if(initFlag)
        {
            initSelectLED();
            initFlag = false;
        }

        selectLED();
        break;
    }
    }
}