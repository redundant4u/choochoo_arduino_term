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
    touchCircleManuel();
}

void gameComplete(void)
{
    tft.setRotation(3);

    tft.fillScreen(WHITE);

    tft.setCursor(80, 80);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("Congratulation!");
    tft.setCursor(70, 115);
    tft.println("You are the best!");

    Timer1.stop();
}

void gameOver(void)
{
    tft.setRotation(3);

    tft.fillScreen(WHITE);

    tft.setCursor(100, 80);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("Game Over...");
    tft.setCursor(60, 115);
    tft.println("Press Reset Button");

    Timer1.stop();
}

TSPoint waitOneTouch(void)
{
    TSPoint p;

    do
    {
        p = ts.getPoint();

        pinMode(XM, OUTPUT); //Pins configures again for TFT control
        pinMode(YP, OUTPUT);

    } while ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE));

    return p;
}