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
  int n = markValids(color, index);

  if(n) row_col = index[rand()%n]; 

  return n ? 1 : 0;
}

void
Board::move(int row, int col, point_t color){
    placeStone(row, col, color);
}

void 
Board::markHasAir(){

}


int 
Board::markCaptures(point_t color, row_col_t *index){
  int cnt = 0;
  for(int r=0; r<size; r++){
    for(int c=0; c<size; c++){
      if(checkCaptured(r, c, color)){
        points[r][c] |= CAPTURED;
        if(index){
          index[cnt].row = r;
          index[cnt].col = c;
        }
        cnt++;
      }
    }
  }
  return cnt;}

int 
Board::checkCaptured(int row, int col, point_t color){
  return 0;
}

void 
Board::removeMarkedCaptures(){
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  do{
    if(*p & CAPTURED) *p &= ~ANY_STONE;
  } while(++p != e);

}

