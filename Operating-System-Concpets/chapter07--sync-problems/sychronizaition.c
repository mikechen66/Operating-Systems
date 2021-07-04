
// figure-07-01.c, The structure of the producer process.

while (true) {
    //. . .
    /* produce an item in next produced */
    //. . .
    wait(empty);
    wait(mutex);
    //. . .
    /* add next produced to the buffer */
    //. . .
    signal(mutex);
    signal(full);
}


// figure-07-02.c, The structure of the consumer process.

    while (true) {
    wait(full);
    wait(mutex);
    //. . .
    /* remove an item from buffer to next consumed */
    //. . .
    signal(mutex);
    signal(empty);
    //. . .
    /* consume the item in next consumed */
    //. . .
}


// figure-07-03.c, The structure of a writer process.

while (true) {
    wait(rw mutex);
    //. . .
    /* writing is performed */
    //. . .
    signal(rw mutex);
}


// figure-07-04.c, The structure of a reader process

while (true) {
    wait(mutex);
    read count++;
    if (read count == 1)
        wait(rw mutex);
    signal(mutex);
    //. . .
    /* reading is performed */
    //. . .
    wait(mutex);
    read count--;
    if (read count == 0)
        signal(rw mutex);
    signal(mutex);
}


// figure-07-05, diagram without code


// figure-07-06.c, The structure of philosopher i.

while (true) {
    wait(chopstick[i]);
    wait(chopstick[(i+1) % 5]);
    //. . .
    /* eat for a while */
    //. . .
    signal(chopstick[i]);
    signal(chopstick[(i+1) % 5]);
    //. . .
    /* think for awhile */
    //. . .
}


// figure-07-07.c, Figure 7.7 A monitor solution to the dining-philosophers problem

monitor DiningPhilosophers {
    enum {THINKING, HUNGRY, EATING} state[5];
    condition self[5];

    void pickup(int i) {
        state[i] = HUNGRY;
        test(i);
        if (state[i] != EATING)
            self[i].wait();
    }

    void putdown(int i) {
        state[i] = THINKING;
        test((i + 4) % 5);
        test((i + 1) % 5);
    }

    void test(int i) {
        if ((state[(i + 4) % 5] != EATING) &&
                (state[i] == HUNGRY) &&
                (state[(i + 1) % 5] != EATING)) {
            state[i] = EATING;
            self[i].signal();
        }
    }

    initialization code() {
        for (int i = 0; i < 5; i++)
            state[i] = THINKING;
    }
}


// figure 7.8 diagram without code



// figure-07-09.c, Bounded buffer using Java synchronization.


public class BoundedBuffer<E> {
    private static final int BUFFER SIZE = 5;

    private int count, in, out;
    private E[] buffer;

    public BoundedBuffer() {
        count = 0;
        in = 0;
        out = 0;
        buffer = (E[]) new Object[BUFFER SIZE];
    }

    /* Producers call this method */
    public synchronized void insert(E item) {
    /* See Figure 7.11 */
    }

    /* Consumers call this method */
    public synchronized E remove() {
    /* See Figure 7.11 */
    }
}

// figure 7.10 withou code


// figure-01-10.c, insert() and remove() methods using wait() and notify().

/* Producers call this method */
public synchronized void insert(E item) {
    while (count == BUFFER SIZE) {
        try {
            wait();
        }
        catch (InterruptedException ie) { }
    }

    buffer[in] = item;
    in = (in + 1) % BUFFER SIZE;
    count++;

    notify();
}

/* Consumers call this method */
public synchronized E remove() {
    E item;

    while (count == 0) {
        try {
            wait();
        }
        catch (InterruptedException ie) { }
    }

    item = buffer[out];
    out = (out + 1) % BUFFER SIZE;
    count--;

    notify();

    return item;
}


// figure 7.12 diagram withou code


// figure-07-13.c, Example using Java condition variables.

/* threadNumber is the thread that wishes to do some work */
public void doWork(int threadNumber) {
    lock.lock();

    try {
        /**
        * If it’s not my turn, then wait
        * until I’m signaled.
        */
        if (threadNumber != turn)
            condVars[threadNumber].await();

        /**
        * Do some work for awhile ...
        */

        /**
        * Now signal to the next thread.
        */
        turn = (turn + 1) % 5;
        condVars[turn].signal();
    }
    catch (InterruptedException ie) { }
    finally {
        lock.unlock();
    }
}