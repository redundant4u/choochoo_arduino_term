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
    Serial.println("LED is : " + String(correctLEDNum + 1));

    selectLEDManuel();
}

void selectLEDManuel()
{
    tft.setCursor(20, 140);
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("Choose LED color");

    tft.setCursor(20, 165);
    tft.println("from r, y, g");

    tft.setCursor(20, 190);
    tft.println("using bluetooth");
}

void selectLED()
{
    int result = correctLED(correctLEDNum);

    switch (result)
    {
    case CORRECT:
        digitalWrite(leds[correctLEDNum], HIGH);
        gameComplete();
        break;

    case FAIL:
    {
        for (int i = 0; i < NUM_OF_PINS; i++)
        {
            digitalWrite(leds[i], HIGH);
        }
        gameOver();
        break;
    }

    case WAIT:
        break;
    }

    delay(100);
}

int correctLED(int pin)
{
    int bluetoothData = receiveDataFromBluetooth();
    int result = WAIT;

    if(bluetoothData > -1)
    {
        Serial.print("Data: ");
        Serial.println(bluetoothData);
        if(bluetoothData == correctLEDNum + 1)
        {
            Serial.println("CLEAR");
            result = CORRECT;
        }

        else
        {
            Serial.println("FAIL");
            result = FAIL;
        }
    }

    return result;
}