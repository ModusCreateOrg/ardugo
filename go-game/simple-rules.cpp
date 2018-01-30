#include "ArduGo.h"
#include "Board.h"

/*
 *  File: simple-simon-rules.cpp
 *  Purpose: Implementation of the Simple Simon rule set.
 *  Author: Don Anderson
 */

#ifdef SIMPLE_RULES

bool_t
Board::checkValid(idx_t row, idx_t col, point_t color){
  if(!isEmpty(row, col))
    return F;

  return T;
}

#endif