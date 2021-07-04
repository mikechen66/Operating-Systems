
/* figure-07-09.java */
/* Bounded buffer using Java synchronization. */

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


/* figure 7.10 */
/* the diagram without code */


/* figure-07-10.java */
/* insert() and remove() methods using wait() and notify(). */ 

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


/* figure 7.12 */
/* the diagram withou code */


/* figure-07-13.java */
/* Example using Java condition variables. */

/* threadNumber is the thread that wishes to do some work */
public void doWork(int threadNumber) {
    lock.lock();

    try {
        /*
         * If it’s not my turn, then wait
         * until I’m signaled.
         */
        if (threadNumber != turn)
            condVars[threadNumber].await();

        /*
         * Do some work for awhile ...
         */

        /*
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