#ifndef _SIDEBAR_H_
#define _SIDEBAR_H_

/*
 *  File: sidebar.h
 *  Purpose: Declaration of sidebar assets.
 *  Author: Don Anderson
 */

enum{
  TITLE_SIDEBAR,
  STATS_SIDEBAR,
  YOUWIN_SIDEBAR,
  GAMEWIN_SIDEBAR,
  MSG_SIDEBAR
}
typedef sidebar_t;

extern sidebar_t cur_sidebar;
extern const char *player_msg;


void render_sidebar(sidebar_t sidebar);
void set_player_msg(const char* msg);

#endif