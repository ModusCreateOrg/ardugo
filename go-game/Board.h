
#ifndef _BOARD_H_
#define _BOARD_H_

struct Board{

static const int size = 9;
int render();  

private:

struct
{
   unsigned int occupied: 1;
   unsigned int color: 1;
} typedef point_t;

point_t points[size][size];
  
};

#endif