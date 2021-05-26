#include<stdio.h>
#include<stdlib.h>
#define MAX_PAS_LEN 500

// Instruction register.
typedef struct ir
{
  int op;
  int l;
  int m;
}ir;

// base pointer and stack pointer.
int bp;
int sp;
int pc;

int main(void)
{
  FILE *fp;
  fp = fopen("input.txt", "r");
  int halt = 1;

  // Read the input to an array.
  int pas[MAX_PAS_LEN];
  int index = 0;
  while (fscanf(fp, "%d", &pas[index]) == 1)
  {
    index++;
  }

  // Initialize bp, sp, pc.
  bp = index;
  sp = index-1;
  pc = 0;

  while (halt == 1)
  {
    // Fetch
    ir.op = pas[pc];
    ir.l = pas[pc + 1];
    ir.m = pas[pc + 2];
    pc += 3;

    // Execute
    switch (ir.op)
    {
      // 01 – LIT 0, M Pushes a constant value (literal) M onto the stack
      case 1:
        sp = sp + 1;
        pas[sp] = ir.m;
        break;
      // 02 – OPR 0, M Operation to be performed on the data at the top of the stack.
      // 03 – LOD L, M Load value to top of stack from the stack location at
      // set M from L lexicographical levels down
      // 04 – STO L, M Store value at top of stack in the stack location at offset M
      // from L lexicographical levels down
      // 05 – CAL L, M Call procedure at code index M (generates new
      // Activation Record and PC <- M)
      // 06 – INC 0, M Allocate M memory words (increment SP by M). First four
      // are reserved to Static Link (SL), Dynamic Link (DL), Return Address (RA), and Parameter (P)
      // 07 – JMP 0, M Jump to instruction M (PC  M)
      // 08 – JPC 0, M Jump to instruction M if top stack element is 0
      // 09 – SYS 0, 1 Write the top stack element to the screen
      //      SYS 0, 2 Read in input from the user and store it on top of the stack
      //      SYS 0, 3 End of program (Set Halt flag to zero)
      dafalut:
        printf("Wrong op code!\n");
        return 0;
    }
  }

  return 0;
}

// int base(int L)
// {
//   int arb = BP; // arb = activation record base
//
//   while ( L > 0) //find base L levels down
//   {
//     arb = pas[base];
//     L--;
//   }
//
//   return arb;
// }
