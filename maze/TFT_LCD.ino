void initLCD(void)
{
  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(3);

  tft.fillScreen(WHITE);

  pinMode(13, OUTPUT);
}

void drawMaze(void)
{
  tft.setCursor(TITLE_TEXT_X, TITLE_TEXT_Y);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("Maze Game");

  // Row fillRect(X, Y, W, MAZE_STROKE)
  // Col fillRect(X, Y, MAZE_STROKE, H)
  tft.setCursor(MAZE_START_X + 5, MAZE_START_Y - 15);
  tft.setTextSize(1);
  tft.println("Start");

  tft.fillCircle(MAZE_START_X + 15, MAZE_START_Y + 5, CIRCLE_RADIUS, RED);

  tft.fillRect(MAZE_START_X, MAZE_START_Y, MAZE_STROKE, MAZE_END_Y, BLACK);
  tft.fillRect(MAZE_START_X + 30, MAZE_START_Y, MAZE_END_X - 30, MAZE_STROKE, BLACK);
  tft.fillRect(MAZE_START_X + MAZE_END_X, MAZE_START_Y, MAZE_STROKE, MAZE_END_Y, BLACK);
  tft.fillRect(MAZE_START_X, MAZE_START_Y + MAZE_END_Y, MAZE_START_X + MAZE_END_X - 50, MAZE_STROKE, BLACK);

  tft.fillRect(MAZE_START_X, MAZE_START_Y + 35, 20, MAZE_STROKE, BLACK);

  tft.fillRect(MAZE_START_X + 40, MAZE_START_Y, MAZE_STROKE, 35, BLACK);
  tft.fillRect(MAZE_START_X + 40, MAZE_START_Y + 35, 25, MAZE_STROKE, BLACK);
  tft.fillRect(MAZE_START_X + 65, MAZE_START_Y + 35, MAZE_STROKE, 60, BLACK);
  tft.fillRect(MAZE_START_X + 65, MAZE_START_Y + 95, 60, MAZE_STROKE, BLACK);
  tft.fillRect(MAZE_START_X + 125, MAZE_START_Y + 95, MAZE_STROKE, 45, BLACK);
  tft.fillRect(MAZE_START_X + 35, MAZE_START_Y + 140, 90, MAZE_STROKE,BLACK);

  tft.fillRect(MAZE_START_X + 30, MAZE_START_Y + 80, 35, MAZE_STROKE, BLACK);

  tft.fillRect(MAZE_START_X, MAZE_START_Y + 110, 40, MAZE_STROKE, BLACK);

  tft.fillRect(MAZE_START_X + 100, MAZE_START_Y, MAZE_STROKE, 65, BLACK);
  tft.fillRect(MAZE_START_X + 100, MAZE_START_Y + 65, 50, MAZE_STROKE, BLACK);
  tft.fillRect(MAZE_START_X + 150, MAZE_START_Y + 30, MAZE_STROKE, 35, BLACK);

  tft.fillRect(MAZE_START_X + 180, MAZE_START_Y + 100, MAZE_STROKE, 60, BLACK);
  tft.fillRect(MAZE_START_X + 180, MAZE_START_Y + 100, 40, MAZE_STROKE, BLACK);

  tft.fillRect(MAZE_START_X + 180, MAZE_START_Y, MAZE_STROKE, 50, BLACK);
  tft.fillRect(MAZE_START_X + 180, MAZE_START_Y + 50, 35, MAZE_STROKE, BLACK);
  tft.fillRect(MAZE_START_X + 215, MAZE_START_Y + 35, MAZE_STROKE, 30, BLACK);

  tft.fillRect(MAZE_START_X + 245, MAZE_START_Y + 85, 35, MAZE_STROKE, BLACK);
  tft.fillRect(MAZE_START_X + 245, MAZE_START_Y + 85, MAZE_STROKE, 45, BLACK);
  tft.fillRect(MAZE_START_X + 220, MAZE_START_Y + 130, 25, MAZE_STROKE, BLACK);

  tft.setCursor(MAZE_END_X - 4, MAZE_START_Y + MAZE_END_Y);
  tft.setTextSize(1);
  tft.println("Goal");
}

boolean checkBoundary(int x, int y)
{
  if(
    ((MAZE_START_X >= x) || (MAZE_START_X + MAZE_END_X <= x)) ||
    ((MAZE_START_Y - 5 >= y) || (MAZE_START_Y + MAZE_END_Y <= y))
  )
    return false;

  else if(checkBoundaryRow(x, y, 0, 15, 35))
    return false;

  else if(checkBoundaryCol(x, y, 40, 0, 35))
    return false;

  else if(checkBoundaryRow(x, y, 40, 65, 35))
    return false;

  else if(checkBoundaryCol(x, y, 65, 35, 95))
    return false;

  else if(checkBoundaryRow(x, y, 30, 65, 80))
    return false;

  else if(checkBoundaryRow(x, y, 60, 125, 95))
    return false;

  else if(checkBoundaryCol(x, y, 125, 95, 140))
    return false;

  else if(checkBoundaryRow(x, y, 30, 125, 140))
    return false;

  else if(checkBoundaryRow(x, y, 0, 40, 110))
    return false;

  else if(checkBoundaryCol(x, y, 100, 0, 65))
    return false;

  else if(checkBoundaryRow(x, y, 100, 150, 65))
    return false;

  else if(checkBoundaryCol(x, y, 150, 30, 65))
    return false;

  else if(checkBoundaryCol(x, y, 180, 0, 50))
    return false;

  else if(checkBoundaryRow(x, y, 180, 215, 50))
    return false;

  else if(checkBoundaryCol(x, y, 215, 35, 65))
    return false;

  else if(checkBoundaryRow(x, y, 245, 300, 85))
    return false;

  else if(checkBoundaryCol(x, y, 245, 85, 130))
    return false;

  else if(checkBoundaryRow(x, y, 220, 245, 130))
    return false;

  else if(checkBoundaryCol(x, y, 180, 100, 220))
    return false;

  else if(checkBoundaryRow(x, y, 180, 220, 100))
    return false;

  return true;
}

boolean checkBoundaryRow(int x, int y, int x1, int x2, int y1)
{
  return ((MAZE_START_X + x1 <= x) && (x <= MAZE_START_X + x2) && (MAZE_START_Y + y1 == y));
}

boolean checkBoundaryCol(int x, int y, int x1, int y1, int y2)
{
  return ((MAZE_START_X + x1 == x) && (MAZE_START_X + y1 <= y) && (y <= MAZE_START_Y + y2));
}

void moveUp(int x, int y)
{
  tft.fillCircle(x, y, CIRCLE_RADIUS, WHITE);
  tft.fillCircle(x, y - MOVE, CIRCLE_RADIUS, RED);
}

void moveRight(int x, int y)
{
  tft.fillCircle(x, y, CIRCLE_RADIUS, WHITE);
  tft.fillCircle(x + MOVE, y, CIRCLE_RADIUS, RED);
}

void moveDown(int x, int y)
{
  tft.fillCircle(x, y, CIRCLE_RADIUS, WHITE);
  tft.fillCircle(x, y + MOVE, CIRCLE_RADIUS, RED);
}

void moveLeft(int x, int y)
{
  tft.fillCircle(x, y, CIRCLE_RADIUS, WHITE);
  tft.fillCircle(x - MOVE, y, CIRCLE_RADIUS, RED);
}