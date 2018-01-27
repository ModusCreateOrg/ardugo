#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: validate.cpp
 *  Purpose: Implementation of move algorithms.
 *  Author: Don Anderson
 */

int
Board::nextMove(point_t color, row_col_t &row_col){

  clearMeta();

  row_col_t index[size2];
  int n = markValids(index);

  if(n) row_col = index[rand()%n]; 

  return n ? 1 : 0;
}

void
Board::move(int row, int col, point_t color){
    placeStone(row, col, color);
}

int 
Board::markCaptures(row_col_t *index){
  return 0;
}

int 
Board::checkCaptured(int row, int col, point_t color){
  return 0;
}
