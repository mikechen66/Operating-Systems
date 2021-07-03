// Listing 4-1: A program to artificially create a zombie

#include <stdio.h>

int main (int argc, char **argv){
    int rc = fork(); // This returns twice
    int child = 0;
    switch (rc){
        case -1:
          /**
            * this only happens if the system is severely low on resources,
            * or the user's process limit (ulimit -u) has been exceeded
            */
            fprintf(stderr, "Unable to fork!\n");
            return (1);
        case 0:
            printf("I am the child! I am born\n");
            child++;
            break;
        default: 
            printf ("I am the parent! Going to sleep and now wait()ing\n");
            sleep(60);
    }
    printf ("%s exiting\n", (child?"child":"parent"));
    return(0);
}


/*
Output 4-1: Output of the sample program from Listing 4-1
Morpheus@Ergo (∼)$ cc a.c –o a        # compiling the program
cc a.c -o a
Morpheus@Ergo (∼)$ ./a &              # running the program in the background
[2] 3620
I am the parent! *Yawn* Going to sleep..
I am the child! I am born!
child exiting
Morpheus@Ergo (∼)$ ps a              # ps "a” shows the STAT column. 
  PID   TT  STAT      TIME COMMAND
  264 s000  Ss     0:00.03 login -pf morpheus
  265 s000  S      0:00.10 -bash
 3611 s000  T      0:00.03 vi a.c
 3620 s000  S      0:00.00 ./a
 3621 s000  Z      0:00.00 (a)
 3623 s000  R+     0:00.00 ps a 3601 s000  R+     0:00.00 ps a
 */