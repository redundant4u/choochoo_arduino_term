#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408TFTLCDLib.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>     // Touch library

#include <math.h>

// Calibrates value
#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

//These are the pins for the shield!
#define YP A1
#define XM A2
#define YM 7
#define XP 6

short TS_MINX=150;
short TS_MINY=120;
short TS_MAXX=920;
short TS_MAXY=940;

// Init TouchScreen:

TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);

// LCD Pin

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4 // Optional : otherwise connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Init LCD

SPFD5408TFTLCDLib tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Dimensions

uint16_t width = 0;
uint16_t height = 0;

// Buttons

#define BUTTONS 3
#define BUTTON_CLEAR 0
#define BUTTON_SHOW 1
#define BUTTON_RESET 2

Adafruit_GFX_Button buttons[BUTTONS];

uint16_t buttons_y = 0;

void setup(void) {

  tft.reset();

  tft.begin(0x9341);

  tft.setRotation(0); // Need for the Mega, please changed for your choice or rotation initial

  width = tft.width() - 1;
  height = tft.height() - 1;

  initializeButtons();

  // Border

  drawBorder();

  // Initial screen
  tft.setCursor (50, 135); //textsize 2기준 y축 10~295
  tft.setTextSize (2);
  tft.setTextColor(BLACK);
  tft.println("Please touch");
  tft.setCursor (75, 155);
  tft.println("the dot");

  delay(2000);
  
  touch_circle();
  touch_circle();
}

// -- Loop

void loop()
{
  
}

// Calibration of Touch Screen (resistive)

void touch_circle(void) {

  TSPoint p1;
  int colors[] = {BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE};
  
  tft.fillScreen(BLACK);

  randomSeed(analogRead(0));

  int randx = random(250);
  int randy = random(300);
  int randr = random(10, 50);
  int randc = random(7);

  tft.fillCircle(randx,randy,randr,colors[randc]); //show the first point 파라미터 : x좌표 y좌표 반지름 색
  delay(50);

  do {

    p1 = waitOneTouch();

  } while (sqrt((mapXValue(p1)-randx)*(mapXValue(p1)-randx)+(mapYValue(p1)-randy)*(mapYValue(p1)-randy)) < randr);

  tft.fillScreen(BLACK);
  delay(50);
}
// wait 1 touch to return the point

TSPoint waitOneTouch() {

  TSPoint p;

  do {
    p= ts.getPoint();

    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));

  return p;
}

// Draw a border

void drawBorder () {

  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 10;

  tft.fillScreen(BLACK);
  tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);

}
// Initialize buttons

void initializeButtons() {

  uint16_t x = 40;
  uint16_t y = height - 20;
  uint16_t w = 75;
  uint16_t h = 20;

  uint8_t spacing_x = 5;

  uint8_t textSize = 1;

  char buttonlabels[3][20] = {"Clear", "Show", "Recalib."};
  uint16_t buttoncolors[15] = {RED, BLUE, RED};

  for (uint8_t b=0; b<3; b++) {
    buttons[b].initButton(&tft,                           // TFT object
                  x+b*(w+spacing_x),  y,                  // x, y,
                  w, h, WHITE, buttoncolors[b], WHITE,    // w, h, outline, fill,
                  buttonlabels[b], textSize);             // text
  }

  // Save the y position to avoid draws

  buttons_y = y;

}

// Map the coordinate X

uint16_t mapXValue(TSPoint p) {

  uint16_t x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

  //Correct offset of touch. Manual calibration
  //x+=1;

  return x;

}

// Map the coordinate Y

uint16_t mapYValue(TSPoint p) {

  uint16_t y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

  //Correct offset of touch. Manual calibration
  //y-=2;

  return y;
}
