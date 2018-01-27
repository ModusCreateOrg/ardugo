#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: validate.cpp
 *  Purpose: Implementation of move validation methods.
 *  Author: Don Anderson
 */

void
Board::move(){

  clearMeta();

  index_t index[size];
  int n = markValids(index);

  if(n){
    int r = rand()%n;
    placeStone(index[r].row, index[r].col, WHITE_STONE);
  }

}