#include "ArduGo.h"
#include "sidebar.h"
#include "assets.h"

/*
 *  File: sidebar.cpp
 *  Purpose: Declaration of sidebar assets.
 *  Author: Don Anderson
 */

sidebar_t cur_sidebar = TITLE_SIDEBAR;
static const char *player_msg = NULL;

void 
set_player_msg(const char* msg){
  cur_sidebar = MSG_SIDEBAR;
  player_msg = msg;
}

PROGMEM const char* const STR_Game    = "Game";
PROGMEM const char* const STR_Black   = "Black ";
PROGMEM const char* const STR_White   = "White ";
PROGMEM const char* const STR_Capt    = " capt ";
PROGMEM const char* const STR_Modus   = "Modus";
PROGMEM const char* const STR_ArduGo  = "ArduGo";
PROGMEM const char* const STR_Hello   = "Hello";

void 
render_sidebar(sidebar_t sidebar){

  switch(sidebar){
    case STATS_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println(STR_Game);
      arduboy.setTextSize(1);
      
      arduboy.println();

      arduboy.print(STR_Black);
      arduboy.println(black_live);
      arduboy.print(STR_Capt);
      arduboy.println(white_capt);

      arduboy.println();
      
      arduboy.print(STR_White);
      arduboy.println(white_live);
      arduboy.print(STR_Capt);
      arduboy.println(black_capt);

      break;

    case TITLE_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println(STR_Modus);
      arduboy.setTextSize(1);
      arduboy.println(STR_ArduGo);
      break;

    case MSG_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println(STR_Hello);
      arduboy.setTextSize(1);
      arduboy.println();
      if(!player_msg)
      arduboy.println();
      else
        arduboy.println(player_msg);
      break;
    }
}

