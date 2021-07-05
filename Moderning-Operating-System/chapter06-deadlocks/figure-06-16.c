
// Figure 6-16. Polite processes that may cause livelock

void process_A(void) {
    acquire_lock(&resource_1);
    while (try_lock(&resource_2) == FAIL) {
        release_lock(&resource_1); 
        wait_fixed_time();
        acquire_lock(&resource_1);
    }
    use_both_resources( ); 
    release_lock(&resource_2); 
    release_lock(&resource_1);
}

void process_A(void) {
    acquire lock(&resource_2);
        while (try lock(&resource_1) == FAIL) {
            release lock(&resource_2); 
            wait fixed time();
            acquire lock(&resource_2);
    }
    use both resources( ); 
    release lock(&resource_1); 
    release lock(&resource_2);
}