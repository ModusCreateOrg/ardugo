
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

int exec(char* line);
int exec(int nargs, const char **argv);
void execSerial();

};//Shell














#endif