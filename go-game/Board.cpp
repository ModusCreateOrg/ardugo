
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
  if(millis() > cursor_millis + 300){
    cursor_millis = millis();
    cursor_color = cursor_color == WHITE ? BLACK : WHITE;
  }
  execButtons();
} 

void 
Board::execButtons(){
  uint8_t buttons = buttons_prev & arduboy.buttonsState();
  if (!(previousButtonState & UP_BUTTON) && (currentButtonState & UP_BUTTON))
    cursorUp();
  if (!(previousButtonState & DOWN_BUTTON) && (currentButtonState & DOWN_BUTTON))
    cursorDown();
  if (!(previousButtonState & LEFT_BUTTON) && (currentButtonState & LEFT_BUTTON))
    cursorLeft();
  if (!(previousButtonState & RIGHT_BUTTON) && (currentButtonState & RIGHT_BUTTON))
    cursorRight();

  if (!(previousButtonState & A_BUTTON) && (currentButtonState & A_BUTTON)){
    if(getPoint(cursor_row, cursor_col)){
      tunes.tone(150, 100);
    }
    else{
      placeStone(cursor_row, cursor_col, BLACK_STONE);
      tunes.tone(2000, 100);
    }
  }
  
  if (!(previousButtonState & B_BUTTON) && (currentButtonState & B_BUTTON))
    clear();
};

void
Board::render(){

  // Draw Background
  drawBitmap(65, 0, board_background);
  
  // Draw Cursor
  if(cursor_color == BLACK)
    arduboy.fillRect(66+7*cursor_col, 57-7*cursor_row, 6, 6, BLACK);

  // Draw Stones
  for(int r=0; r<size; r++){
    for(int c=0; c<size; c++){
      if(getPoint(r,c) & WHITE_STONE){
          arduboy.drawRect(67+7*c, 58-7*r, 4, 4, BLACK);
      }
      else if(getPoint(r,c) & BLACK_STONE){
          arduboy.fillRect(67+7*c, 58-7*r, 4, 4, BLACK);
      }
    }
  }
}

void 
Board::dump(){
  for(int c=0; c < size; c++){
    for(int r=size-1; r >= 0; r--){
      if(getPoint(r,c) & WHITE_STONE)
          Serial.print(" W");
      else if(getPoint(r,c) & BLACK_STONE)
          Serial.print(" B");
      else
        Serial.print(" .");
    }
    Serial.println();
  }
}

void 
Board::clear(){
  cursor_row = cursor_col = 4;
  for(int r=0; r<size; r++){
    for(int c=0; c<size; c++){
      removeStone(r,c);
    }
  }
}




