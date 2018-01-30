#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: validate.cpp
 *  Purpose: Implementation of move algorithms.
 *  Author: Don Anderson
 */

void
Board::move(uint8_t row, uint8_t col, point_t color){
    placeStone(row, col, color);
    clearMeta();
    Board::markHasAir();
    markCaptures(color, NULL);
    removeMarkedCaptures();
}

void 
Board::markHasAir(){
  uint8_t n;
  do{
    n = markHasAirOnce();
  }while(n);
}

uint8_t 
Board::markHasAirOnce(){
  uint8_t cnt = 0;
    for(idx_t r=0; r<size; r++){
      for(idx_t c=0; c<size; c++){
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


uint8_t 
Board::markCaptures(point_t color, row_col_t *index){
  uint8_t cnt = 0;
  for(idx_t r=0; r<size; r++){
    for(idx_t c=0; c<size; c++){
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

bool_t 
Board::checkCaptured(idx_t row, idx_t col, point_t color){
  return !isEmpty(row,col) && !hasAir(row, col);
}

void 
Board::removeMarkedCaptures(){
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  do{
    if(*p & CAPTURED){
      if(*p & WHITE_STONE){
        white_live--;
        white_capt++;
      }
      else{
        black_live--;
        black_capt++;
      }
      *p &= ~ANY_STONE;
    }
  } while(++p != e);
}

