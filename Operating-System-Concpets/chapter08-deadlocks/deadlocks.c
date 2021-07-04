
// figure-08-01.c, Deadlock example.

/* thread one runs in this function */
void *do work one(void *param) {
    pthread mutex lock(&first mutex);
    pthread mutex lock(&second mutex);
    /**
    * Do some work
    */
    pthread mutex unlock(&second mutex);
    pthread mutex unlock(&first mutex);

    pthread exit(0);
}

/* thread two runs in this function */
void *do work two(void *param) {
    pthread mutex lock(&second mutex);
    pthread mutex lock(&first mutex);
    /**
     * Do some work
     */
    pthread mutex unlock(&first mutex);
    pthread mutex unlock(&second mutex);

    pthread exit(0);
}


// figure-08-02.c, Livelock example.

/* thread one runs in this function */
void *do work one(void *param) {
    int done = 0;
    while (!done) {
        pthread mutex lock(&first mutex);
        if (pthread mutex trylock(&second mutex)) {
            /**
             * Do some work
             */
            pthread mutex unlock(&second mutex);
            pthread mutex unlock(&first mutex);
            done = 1;
        }
        else
            pthread mutex unlock(&first mutex);
    }

    pthread exit(0);
}


/* thread two runs in this function */
void *do work two(void *param) {
    int done = 0;

    while (!done) {
        pthread mutex lock(&second mutex);
        if (pthread mutex trylock(&first mutex)) {
            /**
              * Do some work
             */
            pthread mutex unlock(&first mutex);
            pthread mutex unlock(&second mutex);
            done = 1;
            }
        else
            pthread mutex unlock(&second mutex);
    }

    pthread exit(0);
}


// Figure 8.3 ~ 8.6  diagram without code


// figure-08-07.c, Deadlock example with lock ordering

void transaction(Account from, Account to, double amount) {
    mutex lock1, lock2;
    lock1 = get lock(from);
    lock2 = get lock(to);

    acquire(lock1);
        acquire(lock2);
            withdraw(from, amount);
            deposit(to, amount);
        release(lock2);
    release(lock1);
}


// figure 8.8 ~ 8.11 diagrams without code