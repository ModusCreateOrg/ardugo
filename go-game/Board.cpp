
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
  if (wasJustPressed(UP_BUTTON)) cursorUp();
  if (wasJustPressed(DOWN_BUTTON)) cursorDown();
  if (wasJustPressed(LEFT_BUTTON)) cursorLeft();
  if (wasJustPressed(RIGHT_BUTTON)) cursorRight();
 
  if (wasJustPressed(A_BUTTON)){
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
  
  if (wasJustPressed(B_BUTTON)){
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
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  while(p != e){
    if(*p < 0x10) Serial.print("0");
    Serial.print(*p++, HEX);
  }
  Serial.println();
}

void 
Board::print(){
  for(int c=0; c < size; c++){
    for(int r=size-1; r >= 0; r--){

      // stone
      if(isWhite(r,c))
          Serial.print(" W");
      else if(isBlack(r,c))
          Serial.print(" B");
      else
        Serial.print(" .");

      // ISVALID
      if(isValid(r,c))
        Serial.print("v");
      else
        Serial.print("_");

      // ISCAPTURED
      if(isCaptured(r,c))
        Serial.print("c");
      else
        Serial.print("_");

      // HASAIR
      if(hasAir(r,c))
        Serial.print("a");
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
Board::clearMeta(point_t exclude_mask){
  point_t *p = pointsBeg();
  point_t *e = pointsEnd();
  while(p != e) *p++ &= (META_MASK | exclude_mask);
}





