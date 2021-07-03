// Listing 11-7: The wait queue implementation, from osfmk/kern/wait_queue.c

/*
 * wait_queue_t
 * This is the definition of the common event wait queue
 * that the scheduler APIs understand.  It is used
 * internally by the gerneralized event waiting mechanism
 * (assert_wait), and also for items that maintain their
 * own wait queues (such as ports and semaphores).
 *
 * It is not published to other kernel components.  They
 * can create wait queues by calling wait_queue_alloc.
 *
 * NOTE:  Hardware locks are used to protect event wait
 * queues since interrupt code is free to post events to
 * them.
 */

typedef struct wait_queue {
    unsigned int                    /* flags */
    /* boolean_t */     wq_type:16,     /* only public field */
                        wq_fifo:1,      /* fifo wakeup policy? */
                        wq_prepost:1,   /* waitq supports prepost? set only */
                        :0;             /* force to long boundary */
    hw_lock_data_t      wq_interlock;   /* interlock */
    queue_head_t        wq_queue;               /* queue of elements */
} WaitQueue;