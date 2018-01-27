
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "Game.h"
#include "Player.h"

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
        else if(!strcmp(argv[0], "dump-game"))
          game->dump();
        else if(!strcmp(argv[0], "dump-player1"))
          player1->dump();
        else if(!strcmp(argv[0], "dump-player2"))
          player2->dump();
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


