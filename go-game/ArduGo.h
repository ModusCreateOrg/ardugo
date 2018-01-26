
#ifndef _ARGUGO_H_
#define _ARGUGO_H_

/*
 *  File: ArduGo.h
 *  Purpose: Declaration of game-wide assets.
 *  Author: Don Anderson
 */

#include <Arduboy.h>

struct Game;
struct Player;

extern Arduboy arduboy;
extern Game *game;
extern Player *player1, *player2;

int ardugo_setup();
int dump_globals();

void
drawBitmap(uint8_t x, uint8_t y, uint8_t *bitmap);

#endif