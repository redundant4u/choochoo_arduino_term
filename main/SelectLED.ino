#define NUM_OF_PINS 3

#define CORRECT  1
#define FAIL     0
#define WAIT    -1

extern SPFD5408TFTLCDLib tft;

int buttons[] = {28, 30, 32};
int leds[] = {22, 24, 26};
int correctLEDNum;

void initSelectLED()
{
    tft.reset();
    tft.begin(0x9341);
    tft.setRotation(0);

    tft.fillScreen(WHITE);

    for (int i = 0; i < NUM_OF_PINS; i++)
    {
        pinMode(leds[i], OUTPUT);
        pinMode(buttons[i], INPUT);
        digitalWrite(leds[i], LOW);
    }

    randomSeed(analogRead(0));

    correctLEDNum = random(NUM_OF_PINS);
    Serial.println("LED is : " + String(correctLEDNum));

    selectLEDManuel();
}

void selectLEDManuel()
{
    tft.setCursor(35, 140);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("Select one of");

    tft.setCursor(35, 165);
    tft.println("the buttons");
}

void selectLED()
{
    int result = correctLED(correctLEDNum);

    switch (result)
    {
    case CORRECT:
        digitalWrite(leds[correctLEDNum], HIGH);
        break;

    case FAIL:
    {
        for (int i = 0; i < NUM_OF_PINS; i++)
            digitalWrite(leds[i], HIGH);
        break;
    }

    case WAIT:
        break;
    }

    delay(100);
}

int correctLED(int pin)
{
    for (int i = 0; i < NUM_OF_PINS; i++)
    {
        if (digitalRead(buttons[i]))
        {
            if (pin == i)
                return CORRECT;
            return FAIL;
        }
    }

    return WAIT;

    // if(digitalRead(buttons[0]))
    // {
    //   if(pin == 0) return 1;
    //   else return 2;
    // }
    // if(digitalRead(buttons[1]))
    // {
    //   if(pin == 1) return 1;
    //   else return 2;
    // }
    // if(digitalRead(buttons[2]))
    // {
    //   if(pin == 2) return 1;
    //   else return 2;
    // }
    // return 0;
}