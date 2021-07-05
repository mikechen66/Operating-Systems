
// Figure 2-48. A solution to the readers and writers problem

void reader(void) {
    while (TRUE) { 
        down(&mutex);
        rc = rc + 1;
        if (rc == 1) 
            down(&db); 

        up(&mutex);
        read data base( ); 
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