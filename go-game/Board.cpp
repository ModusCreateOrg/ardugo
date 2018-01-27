
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

  if(millis() > button_millis + 75){
    button_millis = millis();
    execButtons();
  }
} 

void 
Board::execButtons(){
  uint8_t buttons = buttons_prev & arduboy.buttonsState();
  if(buttons & UP_BUTTON)
    cursorUp();
  if(buttons & DOWN_BUTTON)
    cursorDown();
  if(buttons & LEFT_BUTTON)
    cursorLeft();
  if(buttons & RIGHT_BUTTON)
    cursorRight();
  buttons_prev = arduboy.buttonsState();
};

void
Board::render(){
  drawBitmap(65, 0, board_background);
  if(cursor_color == BLACK)
    arduboy.fillRect(65 + 7 * cursor_col, 64 - 7 * cursor_row, 6, 6, BLACK);
}



