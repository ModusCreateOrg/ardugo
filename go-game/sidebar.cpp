#include "ArduGo.h"
#include "sidebar.h"

/*
 *  File: sidebar.cpp
 *  Purpose: Declaration of sidebar assets.
 *  Author: Don Anderson
 */

sidebar_t cur_sidebar = TITLE_SIDEBAR;
static const char *sidebar_msg = NULL;

void 
player_msg(const char* msg){
  cur_sidebar = MSG_SIDEBAR;
  sidebar_msg = msg;
}

void 
render_sidebar(sidebar_t sidebar){

  switch(sidebar){
    case TITLE_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println("Modus");
      arduboy.setTextSize(1);
      arduboy.println("ArduGo");
      break;

    case MSG_SIDEBAR:
      arduboy.setCursor(0,0);
      arduboy.setTextSize(2);
      arduboy.println("Hello");
      arduboy.setTextSize(1);
      arduboy.println("");
      if(!sidebar_msg)
        arduboy.println("Never mind.");
      else
        arduboy.println(sidebar_msg);
      break;
    }
}

