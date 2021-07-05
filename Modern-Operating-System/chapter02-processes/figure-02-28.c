
// Figure 2-28. The producer-consumer problem using sem

#define N 100

typedef int semaphore; 
semaphore mutex = 1; 
semaphore empty = N; 
semaphore full = 0;

void producer(void) {
    int item;

    while (TRUE) {
    down(&empty)
    down(&mutex)
    insert_item(item)
    up(&nutex)
    up(&full)
    } 
}


void consumer(void) {
    int item;

    while (TRUE) { 
        down(&full);
        down(&mutex);
        item = remove_item();  
        up(&mutex); 
        up(&empty); 
        consume_item(item);
    }
}