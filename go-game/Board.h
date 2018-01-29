
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 *  File: Board.h
 *  Purpose: Implementation of board data and methods.
 *  Author: Don Anderson
 */

struct Board{


typedef uint8_t point_t;
const point_t WHITE_STONE = 0x01;
const point_t BLACK_STONE = 0x02;
static const int size = 9;

Board(){
  clear();
}

void render();
void clear();
void loop();
void dump();
void print();

int isEmpty(int row, int col){
  return points[row][col] & ANY_STONE ? 0 : 1;
}

void setCursor(int row, int col){
  cursor_row = row;
  cursor_col = col;
}

void placeStone(int row, int col, point_t color){
  points[row][col] = color;
  if(color == WHITE_STONE)
    white_live++;
  else
    black_live++;
}


private:

typedef uint8_t idx_t;
struct {
  idx_t row, col;
} typedef row_col_t;

static const int size2 = size * size;

const point_t ANY_STONE   = 0x03;

const point_t META_MASK   = 0x03;

const point_t VALID_NEXT = 0x04;
const point_t CAPTURED   = 0x08;
const point_t HAS_AIR    = 0x10;
const point_t VISITED    = 0x20;

void cursorUp()    {if(cursor_row < size-1) cursor_row++; else cursor_row = 0;}
void cursorDown()  {if(cursor_row > 0) cursor_row--; else cursor_row = size-1;}
void cursorLeft()  {if(cursor_col > 0) cursor_col--; else cursor_col = size-1;}
void cursorRight() {if(cursor_col < size-1) cursor_col++; else cursor_col = 0;}

void clearMeta(point_t exclude_mask = 0);

void checkValid(point_t color);

unsigned long cursor_millis;
int cursor_row, cursor_col;
uint8_t buttons_prev, cursor_color;
point_t points[size][size];

void execButtons();

uint8_t getPoint(int row, int col){
  return points[row][col];
}

void removeStone(int row, int col){
  points[row][col] = 0;
}

bool_t isWhite(int row, int col){
  return points[row][col] & WHITE_STONE ? T : F;
}
bool_t isBlack(int row, int col){
  return points[row][col] & BLACK_STONE ? T : F;
}
bool_t isCaptured(int row, int col){
  return points[row][col] & CAPTURED ? T : F;
}
bool_t hasAir(int row, int col){
  return points[row][col] & HAS_AIR ? T : F;
}
bool_t isValid(int row, int col){
  return points[row][col] & VALID_NEXT ? T : F;
}
bool_t isVisited(int row, int col){
  return points[row][col] & VISITED ? T : F;
}

point_t *pointPtr(int row, int col){
  return &points[row][col];
}

point_t *pointsBeg(){
  return &points[0][0];
}

point_t *pointsEnd(){
  return &points[0][0] + size2;
}

// VALIDATION
int markValids(point_t color, row_col_t *index);
int checkValid(int row, int col, point_t color);

// MOVE
int nextMove(point_t color, row_col_t &row_col);
void move(int row, int col, point_t color);
int markCaptures(point_t color, row_col_t *index);
void markHasAir();
int markHasAirOnce();
void removeMarkedCaptures();
int checkCaptured(int row, int col, point_t color);

};//Board


extern Board board;

#endif



