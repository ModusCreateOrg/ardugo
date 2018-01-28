#include "ArduGo.h"
#include "sidebar.h"

/*
 *  File: sidebar.cpp
 *  Purpose: Declaration of sidebar assets.
 *  Author: Don Anderson
 */

sidebar_t cur_sidebar = TITLE_SIDEBAR;

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
    }
}

