
// Figure 2-48. A solution to the readers and writers problem

typedef int semaphore; 
semaphore mutex = 1; 
semaphore db = 1;
int rc = 0;


void reader(void) {
    while (TRUE) { 
        down(&mutex);
        rc = rc + 1;
        if (rc == 1) 
            down(&db); 

        up(&mutex);
        read_data_base(); 
        down(&mutex);
        rc = rc − 1;

        if (rc == 0) 
            up(&db); 
        
        up(&mutex);
        use_data_read()
    }
}

void writer(void) {
    while (TRUE) { 
        think_up_data();
        down(&db);
        write_data_base();
        up(&db);
    }
}