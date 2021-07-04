
// Figure 16-1 diagram without code


// figure-16-02.c, C program with buffer-overflow condition.

#include <stdio.h>
#define BUFFER SIZE 0

int main(int argc, char *argv[]) {
    int j = 0;
    char buffer[BUFFER SIZE];
    int k = 0;
    if (argc < 2) {
        return -1;
    }

    strcpy(buffer,argv[1]);
    printf("K is %d, J is %d, buffer is %s∖n", j,k,buffer);
    return 0;
}


// Figure 16-10, diagrams without code