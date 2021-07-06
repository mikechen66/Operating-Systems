
// Figure 2-27. The producer-consumer problem with a fatal race condition.

#define N 100                 /* number of slots in the buffer */
int count = 0;                /* number of items in the buffer */

void producer(void) {
    int item;

    while (TRUE) {
        item = produce        /* generate next item */
        if (count == N) 
            sleep( );
        insert_item(item);    /* put item in buffer */
        count = count + 1;
        if (count == 1) 
            wakeup(consumer); /* was buffer empty? */
    } 
}

void consumer(void) {
    int item;

    while (TRUE) {
        if (count == 0) 
            sleep( );
        item = remove_item( ); /* take item out of buffer */
        count = count − 1;
        if (count == N − 1) 
            wakeup(producer); 
        consume_item(item);    /* printitem*/
    } 
}