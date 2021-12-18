#include "LCD.h"

SPFD5408TFTLCDLib tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);

void initMazeLCD(void)
{
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(3);

  tft.fillScreen(WHITE);

  pinMode(13, OUTPUT);
}

void initTouchCircleLCD(void)
{
  tft.setRotation(0);
  touchCircleManuel();
}

TSPoint waitOneTouch()
{
  TSPoint p;

  do {
    p= ts.getPoint();

    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));

  return p;
}