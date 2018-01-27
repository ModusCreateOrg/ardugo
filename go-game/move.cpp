#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: validate.cpp
 *  Purpose: Implementation of move algorithms.
 *  Author: Don Anderson
 */

void
Board::move(){

  clearMeta();

  index_t index[size2];
  int n = markValids(index);

  if(n){
    int ri = rand()%n;
    placeStone(index[ri].row, index[ri].col, WHITE_STONE);
    setCursor(index[ri].row, index[ri].col);
  }

}