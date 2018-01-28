#ifndef _ARGUGO_H_
#define _ARGUGO_H_

/*
 *  File: ArduGo.h
 *  Purpose: Declaration of game-wide assets.
 *  Author: Don Anderson
 */

#include <Arduboy.h>
#include "local-defines.h"

extern Arduboy arduboy;
extern ArduboyTunes tunes;

extern uint8_t previousButtonState;
extern uint8_t currentButtonState;
extern uint8_t injectButtonState;

extern int black_score, white_score;

void injectButton(uint8_t button);
int wasJustPressed(uint8_t button);

void ardugo_setup();
void dump_globals();
void print_globals();
void clear_stats();

void
drawBitmap(uint16_t x, uint16_t y, uint8_t *bitmap);

#endif
