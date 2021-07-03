// Listing 11-6 The run queue, from osfmk/kern/sched.h

struct runq_stats {
    uint64_t                                count_sum;
    uint64_t                                last_change_timestamp;
};

#if defined(CONFIG_SCHED_TRADITIONAL) || defined(CONFIG_SCHED_PROTO) || defined(CONFIG_SCHED_FIXEDPRIORITY)
struct run_queue {
    int          highq;                  /* highest runnable queue */
    int          bitmap[NRQBM];         /* run queue bitmap array */
    int          count;                 /* # of threads total */
    int          urgency;               /* level of preemption urgency */
    queue_head_t queues[NRQS];          /* one for each priority */
    struct runq_stats       runq_stats;
};
#endif /* defined(CONFIG_SCHED_TRADITIONAL) || defined(CONFIG_SCHED_PROTO) || defined(CONFIG_SCHED_FIXEDPRIORITY) */