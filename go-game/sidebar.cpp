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

void 
render_sidebar(sidebar_t sidebar){

  switch(sidebar){
    case STATS_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println(strings[STR_Game]);
      arduboy.setTextSize(1);
      arduboy.print(strings[STR_Black]);
      arduboy.println(black_score);
      arduboy.print(strings[STR_White]);
      arduboy.println(black_score);
      break;

    case TITLE_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println(strings[STR_Modus]);
      arduboy.setTextSize(1);
      arduboy.println(strings[STR_ArduGo]);
      break;

    case MSG_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println(strings[STR_Hello]);
      arduboy.setTextSize(1);
      arduboy.println("");
      if(!player_msg)
        arduboy.println("");
      else
        arduboy.println(player_msg);
      break;
    }
}

