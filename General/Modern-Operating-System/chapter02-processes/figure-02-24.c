
//  Figure 2-24. Peterson’s solution for achieving mutual exclusion

#define FALSE 0 
#define TRUE  1
#define N     2                     /* Number of processes */

int turn
int interested[N];                  /* All values initially 0 (FALSE) */

void enter_region(int process) {    /* Process is 0 or 1 */
    int other;                      /* Number of the other process */

    other = 1 − process;            /* The opposite of process */
    interested[process] = TRUE;     /* Show that you are interested */
    turn = process;                 /* Set flag */
    while (turn == process && interested[other] == TRUE)  //* Null statement */
}

void leave_region(int process) {    /* Process: who is leaving */  
    interested[process] = FALSE;    /* Indicate departure from critical region */ 
}