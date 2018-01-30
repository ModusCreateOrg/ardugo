#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: validate.cpp
 *  Purpose: Implementation of move validation methods.
 *  Author: Don Anderson
 */

uint8_t
Board::markValids(point_t color, row_col_t *index){
  uint8_t cnt = 0;
  for(uint8_t r=0; r<size; r++){
    for(uint8_t c=0; c<size; c++){
      if(checkValid(r, c, color)){
        points[r][c] |= VALID_NEXT;
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

