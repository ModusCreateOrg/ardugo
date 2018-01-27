
#include "ArduGo.h"
#include "Board.h"
#include "assets.h"

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
    if(!checkValid(cursor_row, cursor_col, BLACK_STONE)){
      tunes.tone(150, 100);
    }
    else{
      move(cursor_row, cursor_col, BLACK_STONE);
      tunes.tone(2000, 100);
      row_col_t next;
      if(nextMove(WHITE_STONE, next)){
        move(next.row, next.col, WHITE_STONE);
        setCursor(next.row, next.col);
      }
    }
  } 
  
  if (!(previousButtonState & B_BUTTON) && (currentButtonState & B_BUTTON)){
    clear();
  }

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
      if(isWhite(r,c)){
          arduboy.drawRect(67+7*c, 58-7*r, 4, 4, BLACK);
      }
      else if(isBlack(r,c)){
          arduboy.fillRect(67+7*c, 58-7*r, 4, 4, BLACK);
      }
    }
  }
}

void 
Board::dump(){
  for(int c=0; c < size; c++){
    for(int r=size-1; r >= 0; r--){

      // stone
      if(isWhite(r,c))
          Serial.print(" W");
      else if(isBlack(r,c))
          Serial.print(" B");
      else
        Serial.print(" .");

      // meta
      if(isValid(r,c))
        Serial.print("v");
      else
        Serial.print("_");
    }
  Serial.println();
  }
}

void 
Board::clear(){
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  while(p != e) *p++ = 0;
  cursor_row = cursor_col = 4;
}

void 
Board::clearMeta(){
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  while(p != e) *p++ &= META_MASK;
}






