
// Figure 2-15. An example program using threads.

#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>

#define NUMBER OF THREADS 10

void *print_hello_world(void *tid) {
    /* This function prints the thread’s identifier and then exits. */ 
    printf("Hello World. Greetings from thread %d\n", tid); 
    pthread exit(NULL);
}

int main(int argc, char *argv[]) {
    /* The main program creates 10 threads and then exits. */ 
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;

    for (i=0; i < NUMBER_OF_THREADS; i++) {
        printf("Main here. Creating thread %d\n", i);
        status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);

        if (status != 0) { 
            printf("Oops. pthread_create returned error code %d\n", status);
            exit(-1); 
        }
    }
    exit(NULL); 
}