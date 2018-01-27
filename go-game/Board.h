
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 *  File: Board.h
 *  Purpose: Implementation of board data and methods.
 *  Author: Don Anderson
 */

struct Board{

typedef uint8_t point_t;

static const int size = 9;
const point_t WHITE_STONE = 0x01;
const point_t BLACK_STONE = 0x02;

Board(){
  clear();
}

void cursorUp()    {if(cursor_row < size-1) cursor_row++; else cursor_row = 0;}
void cursorDown()  {if(cursor_row > 0) cursor_row--; else cursor_row = size-1;}
void cursorLeft()  {if(cursor_col > 0) cursor_col--; else cursor_col = size-1;}
void cursorRight() {if(cursor_col < size-1) cursor_col++; else cursor_col = 0;}

void loop();
void dump();
void render();
void clear();

private:

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


};

extern Board board;

#endif



