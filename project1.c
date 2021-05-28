#include<stdio.h>
#include<stdlib.h>
#define MAX_PAS_LEN 500

// Instruction register.
int op;
int l;
int m;
// base pointer and stack pointer.
int bp;
int sp;
int pc;
// Path array.
int pas[MAX_PAS_LEN];

int base(int L);

int main(void)
{
  FILE *fp;
  fp = fopen("input.txt", "r");
  int halt = 1;

  // Read the input to an array.
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
    op = pas[pc];
    l = pas[pc + 1];
    m = pas[pc + 2];
    pc += 3;
printf("op: %d\n", op);
    // Execute
    switch (op)
    {
      // 01 – LIT 0, M Pushes a constant value (literal) M onto the stack
      case 1:
        sp++;
        pas[sp] = m;
        break;
      // 02 – OPR 0, M Operation to be performed on the data at the top of the stack.
      case 2:
        switch(m)
        {
           case 0:
             sp = bp - 1;
             pc = pas[sp + 3];
             bp = pas[sp + 2];
             break;
           case 1:
             pas[sp] = -pas[sp];
             break;
           case 2:
             sp --;
             pas[sp] += pas[sp + 1];
             break;
           case 3:
             sp --;
             pas[sp] -= pas[sp + 1];
             break;
           case 4:
             sp --;
             pas[sp] *= pas[sp + 1];
             break;
           case 5:
             sp --;
             pas[sp] /= pas[sp + 1];
             break;
           case 6:
            pas[sp] = pas[sp] % 2;
            break;
           case 7:
             sp --;
             pas[sp] %= pas[sp + 1];
             break;
           case 8:
             sp --;
             pas[sp] = pas[sp] == pas[sp + 1];
             break;
           case 9:
             sp --;
             pas[sp] = pas[sp] != pas[sp + 1];
             break;
           case 10:
             sp --;
             pas[sp] = pas[sp] < pas[sp + 1];
             break;
           case 11:
             sp --;
             pas[sp] = pas[sp] <= pas[sp + 1];
             break;
           case 12:
             sp --;
             pas[sp] = pas[sp] > pas[sp + 1];
             break;
           case 13:
             sp --;
             pas[sp] = pas[sp] >= pas[sp + 1];
             break;
          default:
             printf("Wrong M!\n");
             return 0;
        }
        break;
      // 03 – LOD L, M Load value to top of stack from the stack location at
      // set M from L lexicographical levels down
      case 3:
        sp++;
        pas[sp] = pas[base(l) + m];
        break;
      // 04 – STO L, M Store value at top of stack in the stack location at offset M
      // from L lexicographical levels down
      case 4:
        pas[base(l) + m] = pas[sp];
        sp--;
        break;
      // 05 – CAL L, M Call procedure at code index M (generates new
      // Activation Record and PC <- M)
      case 5:
        pas[sp + 1] = base(l); // static link (SL)
        pas[sp + 2] = bp; // dynamic link (DL)
        pas[sp + 3] = pc; // return address (RA)
        bp = sp + 1;
        pc = m;
        break;
      // 06 – INC 0, M Allocate M memory words (increment SP by M). First four
      // are reserved to Static Link (SL), Dynamic Link (DL), Return Address (RA), and Parameter (P)
      case 6:
        sp += m;
        break;
      // 07 – JMP 0, M Jump to instruction M (PC <- M)
      case 7:
        pc = m;
        break;
      // 08 – JPC 0, M Jump to instruction M if top stack element is 0
      case 8:
        if (pas[sp] == 1)
          pc = m;
        sp--;
        break;
      // 09 – SYS 0, 1 Write the top stack element to the screen
      //      SYS 0, 2 Read in input from the user and store it on top of the stack
      //      SYS 0, 3 End of program (Set Halt flag to zero)
      case 9:
        if (m == 1)
        {
          printf("Output result is: %d\n", pas[sp]);
          sp--;
        }
        else if (m == 2)
        {
          sp++;
          printf("Please Enter an Integer: ");
          scanf("%d", &pas[sp]);
        }
        else
          halt = 0;
        break;
      default:
        printf("Wrong op code!\n");
        return 0;
    }
  }
  fclose(fp);
  return 0;
}

int base(int L)
{
  int arb = bp; // arb = activation record base

  while (L > 0) //find base L levels down
  {
    /** BUG here "base" */
    arb = pas[arb];
    L--;
  }

  return arb;
}
