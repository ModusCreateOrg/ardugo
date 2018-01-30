
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "sidebar.h"
#include "assets.h"
#include "MemoryFree.h"
#include <time.h>

/*
 *  File: ArduGo.cpp
 *  Purpose: Implementation of game-wide assets.
 *  Author: Don Anderson
 */

Arduboy arduboy;
ArduboyTunes tunes;
Board board;

uint8_t previousButtonState = 0;
uint8_t currentButtonState = 0;
uint8_t injectButtonState = 0;
uint8_t black_live=0, white_live=0;
uint16_t black_capt=0, white_capt=0;

void
injectButton(uint8_t button){
  injectButtonState |= button;
}

bool_t 
wasJustPressed(uint8_t button){
 return  (injectButtonState & button) ||
         !(previousButtonState & button) && (currentButtonState & button)
         ? T : F;
}

void 
clear_stats(){

}

void
ardugo_setup(){
  srand (time(NULL));
  board.clear();
}

void 
dump_vars(){
  Serial.print(F("black_live"));
  Serial.print(',');
  Serial.print(black_live);
  Serial.print(',');
  
  Serial.print(F("black_capt"));
  Serial.print(',');
  Serial.print(black_capt);
  Serial.print(',');
  
  Serial.print(F("white_live"));
  Serial.print(',');
  Serial.print(white_live);
  Serial.print(',');
  
  Serial.print(F("white_capt"));
  Serial.print(',');
  Serial.print(white_capt);
  Serial.println(); 
}

void 
print_vars(){
  Serial.print(F("black_live: "));
  Serial.println(black_live);
  
  Serial.print(F("black_capt: "));
  Serial.println(black_capt);
  
  Serial.print(F("white_live: "));
  Serial.println(white_live);
  
  Serial.print(F("white_capt: "));
  Serial.println(white_capt);
}

void 
print_sys(){
  Serial.print(F("Free Memory: "));
  Serial.println(freeMemory());
}

void
drawBitmap(uint16_t x, uint16_t y, uint8_t *bitmap){
  arduboy.drawBitmap(x, y, bitmap+2, bitmap[0], bitmap[1] ,WHITE);
}




