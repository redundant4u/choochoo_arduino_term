#include "LCD.h"

#define COUNT_CHECK 4

extern SPFD5408TFTLCDLib tft;
extern boolean initFlag;
extern int stage;

int count = 0;

void touchCircleManuel()
{
    uint16_t width = tft.width() - 1;
    uint16_t height = tft.height() - 1;
    uint8_t border = 10;

    tft.fillScreen(BLACK);
    tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);

    // Initial screen
    tft.setCursor(50, 135); //textsize 2기준 y축 10~295
    tft.setTextSize(2);
    tft.setTextColor(BLACK);
    tft.println("Please touch");
    tft.setCursor(75, 155);
    tft.println("the dot");

    randomSeed(analogRead(0));

    delay(1000);
}

// Map the coordinate X
uint16_t mapXValue(TSPoint p)
{
    short TS_MAXX = 920;
    short TS_MINX = 150;
    
    uint16_t x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    return x;
}

// Map the coordinate Y
uint16_t mapYValue(TSPoint p)
{
    short TS_MAXY = 940;
    short TS_MINY = 120;

    uint16_t y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    return y;
}

void touchCircle(void)
{
    if(count == COUNT_CHECK) { initFlag = true; stage = FindPitch; }

    TSPoint p1;
    unsigned int colors[] = {BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW};

    tft.fillScreen(BLACK);

    int randx = random(tft.width() - 30);
    int randy = random(tft.height() - 30);
    int randr = random(25, 50);
    int randc = random(6);

    tft.fillCircle(randx, randy, randr, colors[randc]); //show the first point 파라미터 : x좌표 y좌표 반지름 색
    delay(50);

    do
    {
        p1 = waitOneTouch();
    } while (sqrt(((mapXValue(p1) - randx) * (mapXValue(p1) - randx)) + ((mapYValue(p1) - randy) * (mapYValue(p1) - randy))) > randr * 2 - 10);

    count++;

    tft.fillScreen(BLACK);
    delay(50);
}