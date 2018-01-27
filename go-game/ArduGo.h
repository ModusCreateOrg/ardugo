
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

const uint8_t BLACK_STONE = 0;
const uint8_t WHITE_STONE = 0;

extern Arduboy arduboy;
extern Game *game;
extern Player *player1, *player2;

extern uint8_t previousButtonState;
extern uint8_t currentButtonState;

void ardugo_setup();
void dump_globals();

void
drawBitmap(uint8_t x, uint8_t y, uint8_t *bitmap);

#endif