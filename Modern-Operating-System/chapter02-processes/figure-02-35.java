
/* Figure 2-35. A solution to the producer-consumer problem in Java. */

public class ProducerConsumer {
    static final int N = 100;                     // constant giving the buffer size
    static producer p = new producer();           // instantiate a new producer thread 
    static consumer c = new consumer();           // instantiate a new consumer thread 
    static our_monitor mon = new our_monitor();   // instantiate a new monitor
    
    public static void main(String args[]) { 
        p.start();                                // start the producer thread 
        c.start();                                // start the consumer thread
    }

    static class producer extends Thread {
        public void run() {                       // run method contains the thread code
            int item;
            while (true) {                        // producer loop
                item = produce_item();
                mon.insert(item); 
            }
        }
        private int produce_item() { ... }        // actually produce 
    }

    static class consumer extends Thread {
        public void run() {                       //run method contains the thread code
            int item;
            while (true) {                        // consumer loop
                item = mon.remove( );
                consume_item (item); 
            }
        }
        private void consume_item(int item) {...} // actually consume 
    }

    static class our_monitor {                    // this is a monitor
        private int buffer[] = new int[N];
        private int count = 0, lo = 0, hi = 0;    // counters and indices

        public synchronized void insert(int val) {
            if (count == N) 
                go_to_sleep();                    // if the buffer is full, go to sleep 
            
            buffer [hi] = val;                    // insert an item into the buffer
            hi = (hi + 1) % N;                    // slot to place next item in
            count = count + 1;                    // one more item in the buffer now
            
            if (count == 1) 
                notify();                         // if consumer was sleeping, wake it up
        }

        public synchronized int remove() { 
            int val;

            if (count == 0) 
                go_to_sleep();                     // if the buffer is empty, go to sleep val = buffer [lo]; // fetch an item from the buffer
            
            lo = (lo + 1) % N;                     // slot to fetch next item from
            count = count − 1;                     // one few items in the buffer
            
            if (count == N − 1) 
                notify();                          // if producer was sleeping, wake it up
            return val; 
        }
        private void go_to_sleep() { 
            try{
                wait();
            } 
            catch(InterruptedException exc) {};
        }
    }        
}
