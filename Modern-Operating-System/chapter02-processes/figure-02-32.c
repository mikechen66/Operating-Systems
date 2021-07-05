
// Figure 2-32. Using threads to solve the producer-consumer problem.

#include <stdio.h>
#include <pthread.h>

#define MAX 1000000000 

pthread mutex t the mutex; 
pthread cond t condc, condp; 
int buffer = 0;

void *producer(void *ptr) { 
    int i;

    for (i= 1; i <= MAX; i++) {
        pthread mutex lock(&the mutex);
        buffer = i;
        pthread_cond_signam(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit()
}

void *consumer(void *ptr) {
    int i;

    for (i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&the_mutex)
        while (buffer ==0 ) 
            pthread_cond_wait(&condc, &the_mutex)
        buffer = 0;
        pthreadcondsignal(&condp);  
        pthread mutex unlock(&the mutex); 
    }
    pthread exit(0); 
}

int main(int argc, char **argv) {
    pthread_t pro, con;
    pthread_mutex_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    pthread_create(&con, 0, producer, 0);
    pthread_create(&pro, 0, producer, 0);
    pthread_join(pro, 0);
    pthread_jion(con, 0);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
}