// Listing 10-15: The processor object, from osfmk/kern/processor.h

struct processor {
    queue_chain_t  processor_queue;/* idle/active queue link,
                                    * MUST remain the first element */
    int            state;          /* one of OFFLINE,SHUTDOWN,START,INACTIVE,
                                    * IDLE, DISPATCHING, or RUNNING */
    struct thread *active_thread,  /* thread running on processor */
                  *next_thread,    /* next thread when dispatched */
                  *idle_thread;    /* this processor's idle thread. */
    processor_set_t         processor_set;  /* assigned set (discussed later) */
    int                     current_pri;    /* priority of current thread */
    sched_mode_t            current_thmode; /* sched mode of current thread */
    int                     cpu_id;         /* platform numeric id */
    timer_call_data_t       quantum_timer;  /* timer for quantum expiration */
    uint64_t                quantum_end;    /* time when current quantum ends */
    uint64_t                last_dispatch;  /* time of last dispatch */
    uint64_t                deadline;      /* current deadline */
    int                     timeslice;     /* quanta before timeslice ends */

   /* Specific thread schedulers defined in the mach kernel require expanding this
    * structure with their own fields—this will be explained next chapter
    */
#if defined(CONFIG_SCHED_TRADITIONAL) || defined(CONFIG_SCHED_FIXEDPRIORITY)
    struct run_queue        runq;                   /* runq for this processor */
    int                     runq_bound_count; /* # of threads bound to this 
                                                   * processor */
#endif
#if defined(CONFIG_SCHED_GRRR)
    struct grrr_run_queue   grrr_runq;      /* Group Ratio Round-Robin runq */
#endif
    processor_meta_t        processor_meta; /* meta data on processor */
    struct ipc_port *       processor_self; /* port for operations */
    processor_t             processor_list; /* all existing processors */
    processor_data_t        processor_data; /* per-processor data */
};