
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "sidebar.h"
#include "assets.h"
#include <time.h>

/*
 *  File: ArduGo.cpp
 *  Purpose: Implementation of game-wide assets.
 *  Author: Don Anderson
 */

Arduboy arduboy;
ArduboyTunes tunes;

Board board;
Shell *shell = NULL;

uint8_t previousButtonState = 0;
uint8_t currentButtonState = 0;
uint8_t injectButtonState = 0;
uint8_t black_live=0, white_live=0;
uint8_t black_capt=0, white_capt=0;
bool_t  exit_shell = F; 

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
clear_stats(){

}

void
ardugo_setup(){
  srand (time(NULL));
  board.clear();
#if defined(ARDUGO_SHELL)
  shell = new Shell();
#endif
}

void 
dump_vars(){
  Serial.print(strings[STR_black_live]);
  Serial.print(",");
  Serial.print(black_live);
  Serial.print(",");
  
  Serial.print(strings[STR_black_capt]);
  Serial.print(",");
  Serial.print(black_capt);
  Serial.print(",");
  
  Serial.print(strings[STR_white_live]);
  Serial.print(",");
  Serial.print(white_live);
  Serial.print(",");
  
  Serial.print(strings[STR_white_capt]);
  Serial.print(",");
  Serial.print(white_capt);
  Serial.println(); 
}

void 
print_vars(){
  Serial.print(strings[STR_black_live]);
  Serial.print(": ");
  Serial.println(black_live);
  
  Serial.print(strings[STR_black_capt]);
  Serial.print(": ");
  Serial.println(black_capt);
  
  Serial.print(strings[STR_white_live]);
  Serial.print(": ");
  Serial.println(white_live);
  
  Serial.print(strings[STR_white_capt]);
  Serial.print(": ");
  Serial.println(white_capt);
}

void
drawBitmap(uint16_t x, uint16_t y, uint8_t *bitmap){
  arduboy.drawBitmap(x, y, bitmap+2, bitmap[0], bitmap[1] ,WHITE);
}




