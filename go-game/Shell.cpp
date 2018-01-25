
#include "Shell.h"


static int
get_mem(int nargs, const char** argv){
  if(nargs < 2)
    return -1;

  int addr = String(argv[1]).toInt();
  int val = *((int*)addr);

  Serial.print("Addr ");
  Serial.print(addr, HEX);
  Serial.print(" = ");
  Serial.println(val, HEX);
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
      break;
    }
    Serial.print("What: ");
    Serial.println(argv[0]);
  }
}


