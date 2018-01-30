
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "assets.h"

/*
 *  File: Shell.cpp
 *  Purpose: Implementation of a rudimentary shell for debugging.
 *  Author: Don Anderson
 */

static bool_t
check_row(const char* arg){
  int row = strtol(arg, NULL, 10);
  if(row < 0){
    Serial.println(F("The row must be greater than 0."));
    return -1;
  }
  if(row >= board.size){
    Serial.println(F("The row must be less than 9."));
    return -1;
  }
  return row;
}

static bool_t
check_col(const char* arg){
  int col = strtol(arg, NULL, 10);
  if(col < 0){
    Serial.println(F("The column must be greater than 0."));
    return -1;
  }
  if(col >= board.size){
    Serial.println(F("The column must be less than 9."));
    return -1;
  }
  return col;
}

static void
set_cursor(int nargs, const char** argv){
  
  if(nargs < 3){
    Serial.println(F("There must at least 2 args"));
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
    Serial.println(F("There must at least 3 args"));
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
        Serial.println(F("The stone color is invalid."));
    }
    else
        Serial.println(F("The point is not empty."));
  }
}

static void
get_mem(int nargs, const char** argv){
  
  if(nargs < 2){
    Serial.println(F("There must at least 1 arg"));
    return;
  }

  long addr = strtol(argv[1], NULL, 16);
  char typ = nargs > 2 ? argv[2][0] : 'i';

  Serial.print(F("Addr 0x"));
  Serial.print(addr, HEX);
  Serial.print(F(" = "));

  switch(typ){
    case 'i':
      Serial.print(*((int*)addr));
      break;
    case 'I':
      Serial.print(F("0x"));
      Serial.print(*((int*)addr), HEX);
      break;
    case 'l':
      Serial.print(*((long*)addr));
      break;
    case 'L':
      Serial.print(F("0x"));
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

  const int buf_size = 32; 

  if(int n = Serial.available()){
      char line[buf_size+1];
      int nread = Serial.readBytesUntil('\n', line, buf_size);
      line[nread > buf_size ? buf_size : nread] = 0;
      
      if(exec(line))
        Serial.println(F("OK"));
      else
        Serial.println(F("ERROR"));

  }
}

bool_t  
Shell::exec(char* line){

  static const int NARGS = 5;
  const char* delim = " \t\n\r";
 
  int nargs = 0;
  const char *argv[NARGS];

  char *tok = strtok(line, delim);

  while (tok && nargs < NARGS) {
    argv[nargs++] = tok;
    tok = strtok(NULL, delim);
  }

  return exec(nargs, argv);
}

bool_t 
Shell::exec(int nargs, const char **argv){
  if(!nargs){
    Serial.println(F("What?"));
    return F;
  }else{
    if(!strcmp(argv[0], "dmp-vars"))
      dump_vars();

    else if(!strcmp(argv[0], "dmp-brd"))
      board.dump();

    else if(!strcmp(argv[0], "vars"))
      print_vars();

    else if(!strcmp(argv[0], "system"))
      print_sys();

    else if(!strcmp(argv[0], "board"))
      board.print();

    else if(!strcmp(argv[0], "stone"))
      place_stone(nargs, argv);

    else if(!strcmp(argv[0], "clear"))
      board.clear();

    else if(!strcmp(argv[0], "cursor"))
      set_cursor(nargs, argv);

    else if(!strcmp(argv[0], "up"))
      injectButton(UP_BUTTON);

    else if(!strcmp(argv[0], "down"))
      injectButton(DOWN_BUTTON);

    else if(!strcmp(argv[0], "left"))
      injectButton(LEFT_BUTTON);

    else if(!strcmp(argv[0], "right"))
      injectButton(RIGHT_BUTTON);

    else if(!strcmp(argv[0][0], "a"))
      injectButton(A_BUTTON);

    else if(!strcmp(argv[0], "b"))
      injectButton(B_BUTTON);

    else if(!strcmp(argv[0], "mem"))
      get_mem(nargs, argv);

    else{
      Serial.println(F("What?"));
      return F;
    }
  }//nargs
  return F;
}


