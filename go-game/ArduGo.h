#ifndef _ARGUGO_H_
#define _ARGUGO_H_

/*
 *  File: ArduGo.h
 *  Purpose: Declaration of game-wide assets.
 *  Author: Don Anderson
 */

#include "local-defines.h"
#include <Arduboy.h>

PROGMEM const char* const version = "0.0";

typedef uint8_t bool_t;
const bool_t T = 1;
const bool_t F = 0;

extern Arduboy arduboy;
extern ArduboyTunes tunes;

extern uint8_t previousButtonState;
extern uint8_t currentButtonState;
extern uint8_t injectButtonState;
extern bool_t  exit_shell; 
extern bool_t  stop_shell; 

extern uint8_t black_live, white_live;
extern uint8_t black_capt, white_capt;

void injectButton(uint8_t button);
int wasJustPressed(uint8_t button);

void ardugo_setup();
void dump_vars();
void print_vars();
void print_sys();
void clear_stats();

void
drawBitmap(uint16_t x, uint16_t y, uint8_t *bitmap);

#endif
