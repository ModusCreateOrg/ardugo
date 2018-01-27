
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 *  File: Board.h
 *  Purpose: Implementation of board data and methods.
 *  Author: Don Anderson
 */

struct Board{

static const int size = 9;

Board(){
  clear();
  cursor_row = cursor_col = 4;
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
uint8_t points[size][size];

void execButtons();
void placeStone(int row, int col, uint8_t color){
  points[row][col] = color;
}

void removeStone(int row, int col){
  points[row][col] = 0;
}


};

extern Board board;

#endif



