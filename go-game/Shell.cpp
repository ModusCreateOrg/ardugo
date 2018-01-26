
#include "ArduGo.h"

static int
get_var(int nargs, const char** argv){
  if(nargs < 2)
    return -1;
}

static int
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

int  
Shell::execSerial(){

  if(int n = Serial.available()){
      char *line = malloc(n+1);
      line[Serial.readBytesUntil('\r', line, n)] = 0;
      exec(line);
      free(line);
  }
}

int  
Shell::exec(char* line){
  tokenize(line);
  exec();
}

int 
Shell::exec(){
  if(nargs){
    switch(argv[0][0]){
      case 'g':
        if(!strcmp(argv[0], "get-mem"))
          return get_mem(nargs, argv);
        if(!strcmp(argv[0], "get-var"))
          return get_mem(nargs, argv);
      break;
    }
    Serial.print("What: ");
    Serial.println(argv[0]);
  }
}


