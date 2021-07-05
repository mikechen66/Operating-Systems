
// Figure 2-27. The producer-consumer problem with a fatal race condition.

#define N 100 

int count = 0;

void producer(void) {
    int item;

    while (TRUE) {
        item = produce
        if (count == N) 
            sleep( );
        insert_item(item);
        count = count + 1;
        if (count == 1) 
            wakeup(consumer);
    } 
}

void consumer(void) {
    int item;

    while (TRUE) {
        if (count == 0) 
            sleep( );
        item = remove_item( );
        count = count − 1;
        if (count == N − 1) 
            wakeup(producer); 
        consumeitem(item);
    } 
}

