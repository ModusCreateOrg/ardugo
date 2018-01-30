#include "ArduGo.h"
#include "Board.h"

/*
 *  File: simple-simon-rules.cpp
 *  Purpose: Implementation of the Simple Simon heuristics.
 *  Author: Don Anderson
 */

#ifdef SIMPLE_PLAY

uint8_t
Board::nextMove(point_t color, row_col_t &row_col){

  clearMeta();

  row_col_t index[size2];
  uint8_t n = markValids(color, index);

  if(n) row_col = index[rand()%n]; 

  return n ? 1 : 0;
}

#endif