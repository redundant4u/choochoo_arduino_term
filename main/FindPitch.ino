#include "LCD.h"
#include <pitches.h>

#define POTENTIOMETER 62
#define SPEAKER 63

extern SPFD5408TFTLCDLib tft;
extern boolean initFlag;
extern int stage;

int iPitches[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, 0};
int randomPitch;
unsigned long timePrev, timeCur;
boolean tFlag = false;

void initFindPitch()
{
    tft.setRotation(3);

    tft.fillScreen(WHITE);

    randomSeed(analogRead(0));
    randomPitch = random(8);

    findPitchManuel();

    tone(SPEAKER, iPitches[randomPitch], 1000);
    delay(1500);
    noTone(SPEAKER);
}

void findPitchManuel()
{
    tft.setCursor(80, 80);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("Guess the sound");

    tft.setCursor(80, 130);
    tft.print("Goal sound:");
    tft.println(String(randomPitch));
}

void findPitch()
{
    int adc = analogRead(POTENTIOMETER);
    int speakerPitch = map(adc, 0, 1023, 0, 7);
    
    if (randomPitch == speakerPitch)
    {
        if (!tFlag)
        {
            timePrev = millis();
            tFlag = true;
        }
        else
        {
            timeCur = millis();

            if (timeCur - timePrev >= 1500)
            {
                Serial.println("Correct!");
                tFlag = false;

                initFlag = true;
                stage = SelectLED;
            }
        }
    }
    else
    {
        tFlag = false;
    }

    tone(SPEAKER, iPitches[speakerPitch]);
    if(stage == SelectLED) { noTone(SPEAKER); }

    tft.fillRect(245, 155, 15, 15, WHITE);

    tft.setCursor(80, 155);
    tft.print("Current sound:");
    tft.println(String(speakerPitch));
    
    delay(500);
}
