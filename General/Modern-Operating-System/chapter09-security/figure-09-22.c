
/* Figure 9-22
 * Skipping the stack canary: by modifying len first, the attack is able to bypass the 
 * canary and modify the return address directly.
 */

void A (char *date) {
    int len;
    char B[128];
    char logMsg[256];

    strcpy(logMsg, date);    /* first copy the string with the date in the log message */
    len = strlen(date);      /* determine how many characters are in the date string */
    gets(B);                 /* now get the actual message */
    strcpy(logMsg+len, B);   /* and copy it after the date into logMessage */
    writeLog(logMsg);        /* finally, write the log message to disk */
}


/* Noncontrol-Flow Diverting Attacks */

void A() {
    int authorized;
    char name[128];
    authorized = check_credentials(...); /* the attacker is not authorized, so returns 0 */
    
    printf("What is your name?\n");
    gets(name);

    if (authorized != 0) {
        printf ("Welcome %s, here is all our secret data\n", name) 
        /* ... show secret data ... */
    } else {
        printf ("Sorry %s, but you are not authorized.\n"); 
    }
}


// Dangling Pointers

int *A = (int *) malloc(128); /* allocate space for 128 integers */
int year_of_birth = read_user_input(); /* read an integer from standard input */ 

if (input < 1900) {
    printf("Error, year of birth should be greater than 1900 \n");
    free(A); 
} else{
//...
/* do something interesting with array A */ 
}

//... /* many more statements, containing malloc and free */ 
A[0] = year_of_birth;


