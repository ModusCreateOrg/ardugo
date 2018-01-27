
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
  cursor_row = cursor_col = 5;
}

void cursorUp()    {if(cursor_row < size-1) cursor_row++; else cursor_row = 0;}
void cursorDown()  {if(cursor_row) cursor_row--; else cursor_row = size-1;}
void cursorLeft()  {if(cursor_col) cursor_col--; else cursor_col = size-1;}
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

unsigned long cursor_millis, button_millis;
uint8_t cursor_row, cursor_col, cursor_color;
uint8_t buttons_prev;
point_t points[size][size];

void execButtons();

};

extern Board board;

#endif



