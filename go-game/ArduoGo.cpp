
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

int ardugo_setup(){

  arduboy.start();
  arduboy.clear();
  board.render();
  arduboy.display();

  return 0;
}

int dump_globals(){
  return 0;
}

void
drawBitmap(uint8_t x, uint8_t y, uint8_t *bitmap){
  arduboy.drawBitmap(64, 0, bitmap+2, bitmap[0], bitmap[1] ,WHITE);
}



