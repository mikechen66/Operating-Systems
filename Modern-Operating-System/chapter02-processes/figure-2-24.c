
//  Figure 2-24. Peterson’s solution for achieving mutual exclusion

#define FALSE 0 
#define TRUE  1
#define       N

int turn
int interested[N];

void enter region(int process){
    int other;

    other = 1 − process;
    interested[process] = TRUE;
    turn = process;               /* set flag */
    while (turn == process && interested[other] == TRUE) 
}

void leave region(int process) {     
    interested[process] = FALSE;    
}