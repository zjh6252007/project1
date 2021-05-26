#include<stdio.h>
#include<stdlib.h>
#define MAX_PAS_LEN 500


typedef struct ir
{
  int op;
  int sp;
  int bp;
}ir;


int main(void)
{
  FILE *fp;
  fp = fopen("read.txt", "r");
  int halt = 1;


  while(halt == 1)
  {

  }

  return 0;
}
