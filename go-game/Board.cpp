
#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

#include <Arduboy.h>

/*
 *  File: Board.cpp
 *  Purpose: Implementation of board data and methods.
 *  Author: Don Anderson
 */

void
Board::loop(){
  if(millis() > cursor_millis + 100){
    cursor_millis = millis();
    toggleCursor();
  }
} 

void
Board::drawBoard(){
  drawBitmap(64, 0, board_background);
}

void 
Board::toggleCursor(){
  if(cursor_state & 0x01){

  }
};

void
Board::render(){
  drawBoard();
}

void
Board::cursorOn(){
 
}

void
Board::cursorOff(){
 
}



