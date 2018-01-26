
#ifndef _SHELL_H_
#define _SHELL_H_

struct Shell {

int exec(char* line);
int execSerial();

private: 

static const int NARGS = 5; 

const char *argv[NARGS];
byte nargs;

int exec();

void tokenize(char* line){

  static const char delim[5] = " \t\n\r";

  nargs = 0;
  char *tok = strtok(line, delim);

  while (tok && nargs < NARGS) {
    argv[nargs++] = tok;
    tok = strtok(NULL, delim);
  }
}


};//class

extern Shell shell;














#endif