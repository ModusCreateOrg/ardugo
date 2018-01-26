
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 *  File: Board.h
 *  Purpose: Implementation of board data and methods.
 *  Author: Don Anderson
 */

struct Board{

static const int size = 9;
int render();  

private:

struct
{
   unsigned int occupied: 1;
   unsigned int color: 1;
} typedef point_t;

uint8_t cursor_row, cursor_col;
point_t points[size][size];

  
};

#endif