
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "Game.h"
#include "Player.h"

/*
 *  File: ArduGo.cpp
 *  Purpose: Implementation of game-wide assets.
 *  Author: Don Anderson
 */

Arduboy arduboy;
ArduboyTunes tunes;

Board board;
Shell shell;

uint8_t previousButtonState = 0;
uint8_t currentButtonState = 0;
uint8_t injectButtonState = 0;

void
injectButton(uint8_t button){
  injectButtonState |= button;
}

int 
wasJustPressed(uint8_t button){
 return  (injectButtonState & button) ||
         !(previousButtonState & button) && (currentButtonState & button)
         ? 1 : 0;
}

void
ardugo_setup(){
  board.clear();
}

void 
dump_globals(){
}

void 
print_globals(){
}

void
drawBitmap(uint16_t x, uint16_t y, uint8_t *bitmap){
  arduboy.drawBitmap(x, y, bitmap+2, bitmap[0], bitmap[1] ,WHITE);
}




