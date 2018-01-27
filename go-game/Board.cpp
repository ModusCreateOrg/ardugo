
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
  if (!(previousButtonState & A_BUTTON) && (currentButtonState & A_BUTTON))
    placeStone(cursor_row, cursor_col, WHITE);
  if (!(previousButtonState & B_BUTTON) && (currentButtonState & B_BUTTON))
    placeStone(cursor_row, cursor_col, BLACK);
};

void
Board::render(){
  drawBitmap(65, 0, board_background);
  if(cursor_color == BLACK)
    arduboy.fillRect(65 + 7 * cursor_col, 57 - 7 * cursor_row, 6, 6, BLACK);
}



