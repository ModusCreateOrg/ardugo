
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
  cursor_row = cursor_col = 4;
}

void cursorUp()    {if(cursor_row < size-1) cursor_row++; else cursor_row = 0;}
void cursorDown()  {if(cursor_row > 0) cursor_row--; else cursor_row = size-1;}
void cursorLeft()  {if(cursor_col > 0) cursor_col--; else cursor_col = size-1;}
void cursorRight() {if(cursor_col < size-1) cursor_col++; else cursor_col = 0;}

void loop();
void dump(){return 0;}
void render();

private:

struct
{
   unsigned int occupied: 1;
   unsigned int color: 1;
} typedef point_t;

unsigned long cursor_millis;
uint8_t cursor_row, cursor_col, cursor_color;
uint8_t buttons_prev;
point_t points[size][size];

void execButtons();
void placeStone(uint8_t row, uint8_t col, uint8_t color){
  point_t point = points[row][col];
  if(!point.occupied){
    point.occupied = 1;
    point.color = color;
  }
}

void removeStone(uint8_t row, uint8_t col){
  points[row][col].occupied = 0;
}


};

extern Board board;

#endif



