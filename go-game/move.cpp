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
    clearMeta();
    Board::markHasAir();
    markCaptures(color, NULL);
    removeMarkedCaptures();
}

void 
Board::markHasAir(){
  int n;
  do{
    n = markHasAirOnce();
  }while(n);
}

int 
Board::markHasAirOnce(){
  int cnt = 0;
    for(int r=0; r<size; r++){
      for(int c=0; c<size; c++){
        point_t color = points[r][c] & ANY_STONE;
        if(!color) continue;
        if(points[r][c] & HAS_AIR) continue;
        
        point_t air_test = color | HAS_AIR;

        if(r > 0){
          point_t pt = points[r-1][c];
          if((!(pt & ANY_STONE)) || ((pt & air_test) == air_test)){
            cnt++;
            points[r][c] |= HAS_AIR;
            continue;
          }
        }

        if(r < size-1){
          point_t pt = points[r+1][c];
          if((!(pt & ANY_STONE)) || ((pt & air_test) == air_test)){
            cnt++;
            points[r][c] |= HAS_AIR;
            continue;
          }
        }

        if(c > 0){
          point_t pt = points[r][c-1];
          if((!(pt & ANY_STONE)) || ((pt & air_test) == air_test)){
            cnt++;
            points[r][c] |= HAS_AIR;
            continue;
          }
        }

        if(c < size-1){
          point_t pt = points[r][c+1];
          if((!(pt & ANY_STONE)) || ((pt & air_test) == air_test)){
            cnt++;
            points[r][c] |= HAS_AIR;
            continue;
          }
        }
      }
    }
  return cnt;
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
  return cnt;
}

int 
Board::checkCaptured(int row, int col, point_t color){
  return !isEmpty(row,col) && !hasAir(row, col);
}

void 
Board::removeMarkedCaptures(){
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  do{
    if(*p & CAPTURED) *p &= ~ANY_STONE;
  } while(++p != e);

}

