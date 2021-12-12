#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408TFTLCDLib.h>
#include <SPFD5408_TouchScreen.h>

#include "TFT_LCD.h"
#include "Joystick.h"

int currentX = MAZE_START_X + 15;
int currentY = MAZE_START_Y + 5;

SPFD5408TFTLCDLib tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup() {
  Serial.begin(9600);

  initLCD();
  drawMaze();

  initJoystick();
}

void loop() {
  int joystickX = analogRead(JOYSTICK_X);
  int joystickY = analogRead(JOYSTICK_Y);
  int joystickZ = digitalRead(JOYSTICK_Z);

  Serial.println(checkBoundary(currentX, currentY));

  switch (joystickStatus(joystickX, joystickY))
  {
    case UP:
      // Serial.println("UP");
      moveUp(currentX, currentY);
      currentY -= MOVE;
      break;
    case RIGHT:
      // Serial.println("RIGHT");
      moveRight(currentX, currentY);
      currentX += MOVE;
      break;
    case DOWN:
      // Serial.println("DOWN");
      moveDown(currentX, currentY);
      currentY += MOVE;
      break;
    case LEFT:
      // Serial.println("LEFT");
      moveLeft(currentX, currentY);
      currentX -= MOVE;
      break;
    default:
      // Serial.println("NOTHING");
      break;
  }

  delay(150);
}
