#ifndef _SIDEBAR_H_
#define _SIDEBAR_H_

/*
 *  File: sidebar.h
 *  Purpose: Declaration of sidebar assets.
 *  Author: Don Anderson
 */

const enum{
  TITLE_SIDEBAR,
  STAT_SIDEBAR
}
typedef sidebar_t;

extern sidebar_t cur_sidebar;

void render_sidebar(sidebar_t sidebar);

#endif