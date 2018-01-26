#ifndef _PLAYER_H_
#define _PLAYER_H_

/*
 *  File: Player.h
 *  Purpose: Implementation of player data and methods.
 *  Author: Don Anderson
 */

struct Player{
  int dump(){return 0;}
};

struct HumanPlayer : Player{

};

struct ComputerPlayer : Player{

};

#endif