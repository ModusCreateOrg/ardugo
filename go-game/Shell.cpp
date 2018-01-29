
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: Shell.cpp
 *  Purpose: Implementation of a rudimentary shell for debugging.
 *  Author: Don Anderson
 */

PROGMEM const char* const STR_what = "What? ";
PROGMEM const char* const STR_ToFewArgs = "Too few args were supplied";
PROGMEM const char* const STR_PointNotEmpty = "The point is not empty";
PROGMEM const char* const STR_InvalidColor = "The stone color is invalid";

static void
what(const char* msg){
  Serial.print(STR_what);
  Serial.println(msg);
}

static void
what(const char* msg1, const char* msg2){
  Serial.print(STR_what);
  Serial.print(msg1);
  Serial.println(msg2);
}

static void
what(const char* msg1, const char* msg2, const char* msg3){
  Serial.print(STR_what);
  Serial.print(msg1);
  Serial.print(msg2);
  Serial.println(msg3);
}

PROGMEM const char* const STR_RowBounds = "The row value must be 0-8";
PROGMEM const char* const STR_ColBounds = "The column value must be 0-8";

static int
check_row(const char* arg){
  int row = strtol(arg, NULL, 10);
  if(row < 0){
    what(STR_RowBounds, arg);
    return -1;
  }
  if(row >= board.size){
    what(STR_RowBounds, arg);
    return -1;
  }
  return row;
}

static int
check_col(const char* arg){
  int col = strtol(arg, NULL, 10);
  if(col < 0){
    what(STR_ColBounds, arg);
    return -1;
  }
  if(col >= board.size){
    what(STR_ColBounds, arg);
    return -1;
  }
  return col;
}

static void
set_cursor(int nargs, const char** argv){
  
  if(nargs < 3){
    what("Too few args, needs 2!");
    return;
  }

  int row = check_row(argv[1]);
  int col = check_col(argv[2]);

  if (row != -1 && col != -1)
    board.setCursor(row, col);

}

static void
place_stone(int nargs, const char** argv){
  
  if(nargs < 4){
    what(STR_ToFewArgs);
    return;
  }

  int row = check_row(argv[1]);
  int col = check_col(argv[2]);

  if (row != -1 && col != -1){
    if(board.isEmpty(row, col)){
      if(toupper(argv[3][0]) == 'W')
        board.placeStone(row, col, board.WHITE_STONE);
      if(toupper(argv[3][0]) == 'B')
        board.placeStone(row, col, board.BLACK_STONE);
      else
        what(STR_InvalidColor, argv[3]);
    }
    else
      what(STR_PointNotEmpty, argv[1], argv[2]);
  }
}

static void
get_mem(int nargs, const char** argv){
  
  if(nargs < 2){
    what(STR_ToFewArgs);
    return;
  }

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

PROGMEM const char* const STR_OK    = "OK";
PROGMEM const char* const STR_ERROR = "ERROR";

void  
Shell::execSerial(){

  const int buf_size = 32; 

  if(int n = Serial.available()){
      char line[buf_size+1];
      int nread = Serial.readBytesUntil('\n', line, buf_size);
      line[nread > buf_size ? buf_size : nread] = 0;
      
      if(exec(line) < 0)
        Serial.println(STR_ERROR);
      else
        Serial.println(STR_OK);
  }
}

PROGMEM const char* const STR_Delim = " \t\n\r";

int  
Shell::exec(char* line){

  static const int NARGS = 5; 
  int nargs = 0;
  const char *argv[NARGS];

  char *tok = strtok(line, STR_Delim);

  while (tok && nargs < NARGS) {
    argv[nargs++] = tok;
    tok = strtok(NULL, STR_Delim);
  }

  return exec(nargs, argv);
}

PROGMEM const char* const STR_Exit        = "exit";
PROGMEM const char* const STR_PrintSys    = "print-sys";
PROGMEM const char* const STR_DumpVars    = "dump-vars";
PROGMEM const char* const STR_DumpBoard   = "dump-board";
PROGMEM const char* const STR_PrintVars   = "print-vars";
PROGMEM const char* const STR_PrintBoard  = "print-board";
PROGMEM const char* const STR_PlaceStone  = "place-stone";
PROGMEM const char* const STR_ClearBoard  = "clear-board";
PROGMEM const char* const STR_SetCursor   = "set-cursor";
PROGMEM const char* const STR_GetMem      = "get-mem";

PROGMEM const char* const STR_ButtonU    = "button-up";
PROGMEM const char* const STR_ButtonD    = "button-down";
PROGMEM const char* const STR_ButtonL    = "button-left";
PROGMEM const char* const STR_ButtonR    = "button-right";
PROGMEM const char* const STR_ButtonA    = "button-a";
PROGMEM const char* const STR_ButtonB    = "button-b";

int 
Shell::exec(int nargs, const char **argv){
  if(nargs){
    switch(argv[0][0]){

      case 'd':
        if(!strcmp(argv[0], STR_DumpVars))
          dump_vars();
        else if(!strcmp(argv[0], STR_DumpBoard))
          board.dump();
        else
          what(argv[0]);
        break;

      case 'p':
        if(!strcmp(argv[0], STR_PrintVars))
          print_vars();
        if(!strcmp(argv[0], STR_PrintSys))
          print_sys();
        else if(!strcmp(argv[0], STR_PrintVars))
          board.print();
        else if(!strcmp(argv[0], STR_PlaceStone))
          place_stone(nargs, argv);
        else
          what(argv[0]);
        break;

      case 'c':
        if(!strcmp(argv[0], STR_ClearBoard))
          board.clear();
        else
          what(argv[0]);
        break;

      case 's':
        if(!strcmp(argv[0], STR_SetCursor))
          set_cursor(nargs, argv);
        else
          what(argv[0]);
        break;

      case 'e':
        if(!strcmp(argv[0], STR_Exit))
          exit_shell = T;
        else
          what(argv[0]);
        break;

      case 'b':
        if(!strcmp(argv[0], STR_ButtonU))
          injectButton(UP_BUTTON);
        else if(!strcmp(argv[0], STR_ButtonD))
          injectButton(DOWN_BUTTON);
        else if(!strcmp(argv[0], STR_ButtonL))
          injectButton(LEFT_BUTTON);
        else if(!strcmp(argv[0], STR_ButtonR))
          injectButton(RIGHT_BUTTON);
        else if(!strcmp(argv[0], STR_ButtonA))
          injectButton(A_BUTTON);
        else if(!strcmp(argv[0], STR_ButtonB))
          injectButton(B_BUTTON);
        else
          what(argv[0]);
        break;

      case 'g':
        if(!strcmp(argv[0], STR_GetMem))
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


