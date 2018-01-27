
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
Board board;
Shell shell;

Game  *game;
Player *player1, *player2;

uint8_t previousButtonState = 0;
uint8_t currentButtonState = 0;

void
ardugo_setup(){
  board.clear();
}

void 
dump_globals(){
}

void
drawBitmap(uint16_t x, uint16_t y, uint8_t *bitmap){
  arduboy.drawBitmap(x, y, bitmap+2, bitmap[0], bitmap[1] ,WHITE);
}




