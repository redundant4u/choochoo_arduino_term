#define SEGMENT_DELAY 5

unsigned long segTimePrev, segTimeCur;

byte patterns[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};
int digitSelectPin[] = {64, 65, 66, 67};
int segmentPin[] = {40, 41, 42, 43, 44, 45, 46, 47};
int seconds = 100;

void initSegment()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(digitSelectPin[i], OUTPUT);
    }
    for (int i = 0; i < 8; i++)
    {
        pinMode(segmentPin[i], OUTPUT);
    }
    segTimePrev = millis();
}

void showDigit(int pos, int number)
{
    for (int i = 0; i < 4; i++)
    {
        if (i + 1 == pos)
        {
            digitalWrite(digitSelectPin[i], LOW);
        }
        else
        {
            digitalWrite(digitSelectPin[i], HIGH);
        }
    }
    
    for (int i = 0; i < 8; i++)
    {
        boolean on_off = bitRead(patterns[number], 7 - i);
        digitalWrite(segmentPin[i], on_off);
    }
}

void show4Digit(int number)
{
    number = number % 10000;

    int thousands = number / 1000;
    number = number % 1000;

    int hundreads = number / 100;
    number = number % 100;

    int tens = number / 10;
    int ones = number % 10;

    showDigit(1, thousands);
    delay(SEGMENT_DELAY);
    showDigit(2, hundreads);
    delay(SEGMENT_DELAY);
    showDigit(3, tens);
    delay(SEGMENT_DELAY);
    showDigit(4, ones);
    delay(SEGMENT_DELAY);
}

void startTimer()
{
    if(seconds == 0) { gameOver(); }

    segTimeCur = millis();
    if (segTimeCur - segTimePrev >= 1000)
    {
        segTimePrev = segTimeCur;
        seconds--;
        if (seconds <= 0)
        {
            seconds = 0;
        }
    }
    show4Digit(seconds);
}