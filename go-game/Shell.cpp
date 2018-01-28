
#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"

/*
 *  File: Shell.cpp
 *  Purpose: Implementation of a rudimentary shell for debugging.
 *  Author: Don Anderson
 */

static void
what(const char* msg){
  Serial.print("What: ");
  Serial.println(msg);
}

static void
what(const char* msg1, const char* msg2){
  Serial.print("What: ");
  Serial.print(msg1);
  Serial.println(msg2);
}

static void
what(const char* msg1, const char* msg2, const char* msg3){
  Serial.print("What: ");
  Serial.print(msg1);
  Serial.print(msg2);
  Serial.println(msg3);
}

static int
check_row(const char* arg){
  int row = strtol(arg, NULL, 10);
  if(row < 0){
    what("The row is below zero: ", arg);
    return -1;
  }
  if(row >= board.size){
    what("The row is above 8: ", arg);
    return -1;
  }
  return row;
}

static int
check_col(const char* arg){
  int col = strtol(arg, NULL, 10);
  if(col < 0){
    what("The column is below zero: ", arg);
    return -1;
  }
  if(col >= board.size){
    what("The column is above 8: ", arg);
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
    what("Too few args, needs 3!");
    return;
  }

  int row = check_row(argv[1]);
  int col = check_col(argv[2]);

  if (row != -1 && col != -1){
    if(board.isEmpty(row, col)){
      if(!strcmp(argv[3], "W"))
        board.placeStone(row, col, board.WHITE_STONE);
      else if(!strcmp(argv[3], "B"))
        board.placeStone(row, col, board.BLACK_STONE);
      else
        what("Invalid color:", argv[3]);
    }
    else
      what("The point is not empty: ", argv[1], argv[2]);
  }
}


static void
get_mem(int nargs, const char** argv){
  
  if(nargs < 2){
    what("Too few args, needs 1!");
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

void  
Shell::execSerial(){

  if(int n = Serial.available()){
      char line[33];
      line[Serial.readBytesUntil('\n', line, sizeof(line)-1)] = 0;
      if(exec(line) < 0)
        Serial.println("ERROR");
      else
        Serial.println("OK");
  }
}

int  
Shell::exec(char* line){
  tokenize(line);
  return exec();
}

int 
Shell::exec(){
  if(nargs){
    switch(argv[0][0]){

      case 'd':
        if(!strcmp(argv[0], "dump-vars"))
          dump_vars();
        else if(!strcmp(argv[0], "dump-board"))
          board.dump();
        else
          what(argv[0]);
        break;

      case 'p':
        if(!strcmp(argv[0], "print-vars"))
          print_vars();
        else if(!strcmp(argv[0], "print-board"))
          board.print();
        else if(!strcmp(argv[0], "place-stone"))
          place_stone(nargs, argv);
        else
          what(argv[0]);
        break;

      case 'c':
        if(!strcmp(argv[0], "clear-board"))
          board.clear();
        else
          what(argv[0]);
        break;

      case 's':
        if(!strcmp(argv[0], "set-cursor"))
          set_cursor(nargs, argv);
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
        else if(!strcmp(argv[0], "button-A"))
          injectButton(A_BUTTON);
        else if(!strcmp(argv[0], "button-B"))
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


