#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "Game.h"
#include "Player.h"

/*
 *  File: go-game.ino
 *  Purpose: Implementation of Arduino entry-points.
 *  Author: Don Anderson
 */

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Begin setup()");

  game = new GoGame();
  player1 = new HumanPlayer();
  player2 = new HumanPlayer();

  arduboy.start();
  ardugo_setup();

  Serial.println("End setup()");
}

void loop() {
  Serial.println("loop1");
  board.loop();
  shell.loop();
  arduboy.clear();
  board.render();
  arduboy.display();
}
