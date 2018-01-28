#ifndef _SIDEBAR_H_
#define _SIDEBAR_H_

/*
 *  File: sidebar.h
 *  Purpose: Declaration of sidebar assets.
 *  Author: Don Anderson
 */

enum{
  TITLE_SIDEBAR,
  STAT_SIDEBAR,
  YOUWIN_SIDEBAR,
  GAMEWIN_SIDEBAR,
  MSG_SIDEBAR
}
typedef sidebar_t;

extern sidebar_t cur_sidebar;
extern const char *sidebar_msg;


void render_sidebar(sidebar_t sidebar);
void player_msg(const char* msg);

#endif