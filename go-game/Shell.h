
#ifndef _SHELL_H_
#define _SHELL_H_

/*
 *  File: Shell.h
 *  Purpose: Declaration of a rudimentary shell for debugging.
 *  Author: Don Anderson
 */

struct Shell {

void dump();

void
Shell::loop(){
  execSerial();
}

private: 

bool_t exec(char* line);
bool_t exec(int nargs, const char **argv);
void execSerial();

};//Shell














#endif