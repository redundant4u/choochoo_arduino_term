#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408TFTLCDLib.h>
#include <SPFD5408_TouchScreen.h>

#include "TFT_LCD.h"

SPFD5408TFTLCDLib tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() {
  Serial.begin(9600);

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(3);

  tft.fillScreen(WHITE);

  tft.setCursor(60, 50);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.println("Maze Game");

  pinMode(13, OUTPUT);

  Serial.println("Start");
}

void loop() {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  waitOneTouch();

  Serial.print("X: ");
  Serial.println(p.x);
  Serial.print("Y: ");
  Serial.println(p.y);
}

TSPoint waitOneTouch() {
  TSPoint p;

  do {
    p= ts.getPoint();

    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));

  return p;
}