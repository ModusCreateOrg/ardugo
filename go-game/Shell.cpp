
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"

/*
 *  File: Shell.cpp
 *  Purpose: Implementation of a rudimentary shell for debugging.
 *  Author: Don Anderson
 */


static void
get_mem(int nargs, const char** argv){
  if(nargs < 2)
    return -1;

  long addr = strtol(argv[1], NULL, 16);
  char typ = nargs > 2 ? argv[2][0] : 'i';

  Serial.print("Addr 0x");
  Serial.print(addr, HEX);
  Serial.print(" = ");

  switch(typ){
    case 'i':
      Serial.print(*((int*)addr));
      break;
    case 'I':
      Serial.print("0x");
      Serial.print(*((int*)addr), HEX);
      break;
    case 'l':
      Serial.print(*((long*)addr));
      break;
    case 'L':
      Serial.print("0x");
      Serial.print(*((long*)addr), HEX);
      break;
    case 'f':
    case 'F':
      Serial.print(*((float*)addr));
      break;
    case 'd':
    case 'D':
      Serial.print(*((double*)addr));
      break;
  }
  Serial.println((char)tolower(typ));
  return 0;
}

void  
Shell::execSerial(){

  if(int n = Serial.available()){
      char line[33];
      line[Serial.readBytesUntil('\r', line, sizeof(line)-1)] = 0;
      exec(line);
  }
}

void  
Shell::exec(char* line){
  tokenize(line);
  exec();
}

static void
what(const char* arg0){
  Serial.print("What: ");
  Serial.println(arg0);
}

void 
Shell::exec(){
  if(nargs){
    switch(argv[0][0]){

      case 'd':
        if(!strcmp(argv[0], "dump-globals"))
          dump_globals();
        else if(!strcmp(argv[0], "dump-board"))
          board.dump();
        else
          what(argv[0]);
        break;

      case 'p':
        if(!strcmp(argv[0], "print-globals"))
          print_globals();
        else if(!strcmp(argv[0], "print-board"))
          board.print();
        else
          what(argv[0]);
        break;

      case 'b':
        if(!strcmp(argv[0], "button-up"))
          injectButton(UP_BUTTON);
        else if(!strcmp(argv[0], "button-down"))
          injectButton(DOWN_BUTTON);
        else if(!strcmp(argv[0], "button-left"))
          injectButton(LEFT_BUTTON);
        else if(!strcmp(argv[0], "button-right"))
          injectButton(RIGHT_BUTTON);
        else if(!strcmp(argv[0], "button-a"))
          injectButton(A_BUTTON);
        else if(!strcmp(argv[0], "button-b"))
          injectButton(B_BUTTON);
        else
          what(argv[0]);
        break;

      case 'g':
        if(!strcmp(argv[0], "get-mem"))
          get_mem(nargs, argv);
        else
          what(argv[0]);
        break;

      default:
        what(argv[0]);
        break;
    }

  }
}


