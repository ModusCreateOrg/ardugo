
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 *  File: Board.h
 *  Purpose: Implementation of board data and methods.
 *  Author: Don Anderson
 */

struct Board{

Board(){
  clear();
}

void render();
void clear();
void loop();
void dump();

private:

typedef uint8_t point_t;
typedef uint8_t idx_t;
struct {
  idx_t row, col;
} typedef index_t;

static const int size = 9;
static const int size2 = size * size;

const point_t WHITE_STONE = 0x01;
const point_t BLACK_STONE = 0x02;
const point_t ANY_STONE   = 0x03;

const point_t META_MASK   = 0x03;
const point_t VALID_NEXT  = 0x04;

void cursorUp()    {if(cursor_row < size-1) cursor_row++; else cursor_row = 0;}
void cursorDown()  {if(cursor_row > 0) cursor_row--; else cursor_row = size-1;}
void cursorLeft()  {if(cursor_col > 0) cursor_col--; else cursor_col = size-1;}
void cursorRight() {if(cursor_col < size-1) cursor_col++; else cursor_col = 0;}

void clearMeta();
void checkValid(point_t color);

unsigned long cursor_millis;
int cursor_row, cursor_col;
uint8_t buttons_prev, cursor_color;
point_t points[size][size];

void execButtons();
void move();

uint8_t getPoint(int row, int col){
  return points[row][col];
}

void setCursor(int row, int col){
  cursor_row = row;
  cursor_col = col;
}

void placeStone(int row, int col, point_t color){
  points[row][col] = color;
}

void removeStone(int row, int col){
  points[row][col] = 0;
}

int isEmpty(int row, int col){
  return points[row][col] & ANY_STONE ? 0 : 1;
}
int isWhite(int row, int col){
  return points[row][col] & WHITE_STONE ? 1 : 0;
}
int isBlack(int row, int col){
  return points[row][col] & BLACK_STONE ? 1 : 0;
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

int markValids(index_t *index);
int checkValid(int row, int col, point_t color);


int isValid(int row, int col){
  return points[row][col] & VALID_NEXT ? 1 : 0;
}

};//Board


extern Board board;

#endif



