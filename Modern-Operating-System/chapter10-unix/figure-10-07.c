
// Figure 10-7. A highly simplified shell


while(TRUE) {                          /* repeat forever */
    type_prompt();                     /* display prompt on the screen */ 
    read_command(command, params);     /* read input line from keyboard */

    pid = fork();                      /* fork off a child process */
    if (pid < 0) {
    printf("Unable to fork0");         /* error condition */ 
    continue;                          /* repeat the loop */
    }

    if (pid != 0) {
        waitpid(−1, &status, 0);       /* parent waits for child */ 
    } else {
        execve(command, params, 0);    /* child does the work */
    }
}