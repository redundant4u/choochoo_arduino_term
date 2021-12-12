#define LCD_CS      A3
#define LCD_CD      A2
#define LCD_WR      A1
#define LCD_RD      A0
#define LCD_RESET   A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TITLE_TEXT_X 110
#define TITLE_TEXT_Y 30

#define MAZE_START_X    20
#define MAZE_START_Y    60
#define MAZE_STROKE     3
#define MAZE_END_X      280
#define MAZE_END_Y      160

#define MOVE            5

#define CIRCLE_RADIUS   3

void initLCD(void);
void drawMaze(void);

boolean checkBoundary(int x, int y);

void moveUp(int x, int y);
void moveRight(int x, int y);
void moveDown(int x, int y);
void moveLeft(int x, int y);