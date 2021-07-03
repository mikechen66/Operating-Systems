// Listing 11-1: The Mach thread structure, from osfmk/kern/thread.h

struct thread {
        /*
         * NOTE:   The runq field in the thread structure has an unusual
         * locking protocol.  If its value is PROCESSOR_NULL, then it is
         * locked by the thread_lock, but if its value is something else
         * then it is locked by the associated run queue lock.
         *
         * When the thread is on a wait queue, these first three fields
         * are treated as an unofficial union with a wait_queue_element.
         * If you change these, you must change that definition as well         
         * (kern/wait_queue.h).
         */
        /* Items examined often, modified infrequently */
        queue_chain_t   links;                  /* run/wait queue links */
        processor_t     runq;                   /* run queue assignment */
        wait_queue_t    wait_queue;             /* wait queue we are currently on */
        event64_t       wait_event;             /* wait queue event */
        integer_t       options;                /* options set by thread itself */
#define TH_OPT_INTMASK          0x03            /* interrupt / abort level */
#define TH_OPT_VMPRIV           0x04            /* may allocate reserved memory */
#define TH_OPT_DTRACE           0x08            /* executing under dtrace_probe */
#define TH_OPT_SYSTEM_CRITICAL  0x10            /* Thread must always be allowed to run - even under heavy load */
        /* Data updated during assert_wait/thread_wakeup */
        decl_simple_lock_data(,sched_lock)      /* scheduling lock (thread_lock()) */
        decl_simple_lock_data(,wake_lock)       /* for thread stop / wait (wake_lock()) */
        boolean_t               wake_active;    /* wake event on stop */
        int                     at_safe_point;  /* thread_abort_safely allowed */
        ast_t                   reason;         /* why we blocked */
        wait_result_t           wait_result;    /* outcome of wait may be examined by this thread WITHOUT locking */
        thread_continue_t       continuation;   /* continue here next dispatch */
        void *parameter;                        /* continuation parameter */
        /* Data updated/used in thread_invoke */
        struct funnel_lock  *funnel_lock;           /* Non-reentrancy funnel */
        int                  funnel_state;
#define TH_FN_OWNED             0x1                             /* we own the funnel */
#define TH_FN_REFUNNEL          0x2                             /* re-acquire funnel on dispatch */
        vm_offset_t             kernel_stack;      /* current kernel stack */
        vm_offset_t             reserved_stack;    /* reserved kernel stack */
        /* Thread state: */
        int                     state;
/*
 *      Thread states [bits or'ed]
 */
#define TH_WAIT                 0x01               /* queued for waiting */
#define TH_SUSP                 0x02               /* stopped or requested to stop */
#define TH_RUN                  0x04               /* running or on runq */
#define TH_UNINT                0x08               /* waiting uninteruptibly
#define TH_TERMINATE            0x10               /* halted at termination */
#define TH_TERMINATE2           0x20               /* added to termination queue */
#define TH_IDLE                 0x80               /* idling processor */
        /* Scheduling information */
        sched_mode_t            sched_mode;        /* scheduling mode */
        sched_mode_t            saved_mode;        /* saved mode during forced mode demotion */
        // Bitmask of miscellaneous TH_SFLAG bits
        unsigned int            sched_flags;       /* current flag bits */
        integer_t               sched_pri;         /* scheduled (current) priority */
        integer_t               priority;          /* base priority */
        integer_t               max_priority;      /* max base priority */
        integer_t               task_priority;     /* copy of task base priority */
        integer_t               promotions;        /* level of promotion */
        integer_t               pending_promoter_index;
        void                    *pending_promoter[2];
        integer_t               importance;        /* task-relative importance */
                                                   /* real-time parameters */
        struct {                                   /* see mach/thread_policy.h */
        uint32_t                period;
        uint32_t                computation;
        uint32_t                constraint;
        boolean_t               preemptible;
        uint64_t                deadline;
        }                       realtime;
        uint32_t                was_promoted_on_wakeup;
        uint32_t                current_quantum;   /* duration of current quantum */
        uint64_t  last_run_time;                   /* time when thread was switched away from */
        uint64_t  last_quantum_refill_time;        /* time current_quantum refilled after expiration */
        /* Data used during setrun/dispatch */
        timer_data_t   system_timer;               /* system mode timer */
        processor_t    bound_processor;            /* bound to a processor? */
        processor_t    last_processor;             /* processor last dispatched on */
        processor_t    chosen_processor;         /* Where we want to run this thread */
        /* Fail-safe computation since last unblock or qualifying yield */
        uint64_t       computation_metered;
        uint64_t       computation_epoch;
        uint64_t       safe_release;             /* when to release fail-safe */
        /* Call out from scheduler */
        void (*sched_call)(int type, thread_t thread);
#if defined(CONFIG_SCHED_PROTO)
        uint32_t       runqueue_generation;      /* last time runqueue was drained */
#endif

/* Statistics and timesharing calculations */
#if defined(CONFIG_SCHED_TRADITIONAL)
        natural_t    sched_stamp;                /* last scheduler tick */
        natural_t    sched_usage;                /* timesharing cpu usage [sched] */
        natural_t    pri_shift;                  /* usage -> priority from pset */
        natural_t    cpu_usage;                  /* instrumented cpu usage [%cpu] */
        natural_t    cpu_delta;                  /* accumulated cpu_usage delta */
#endif
        uint32_t     c_switch;                   /* total context switches */
        uint32_t     p_switch;                   /* total processor switches */
        uint32_t     ps_switch;                  /* total pset switches */
  
        /* Timing data structures */
        timer_data_t user_timer;                 /* user mode timer */
        uint64_t     user_timer_save;            /* saved user timer value */
        uint64_t     system_timer_save;          /* saved system timer value */
        uint64_t     vtimer_user_save;           /* saved values for vtimers */
        uint64_t     vtimer_prof_save;
        uint64_t     vtimer_rlim_save;
        /* Timed wait expiration */
        timer_call_data_t       wait_timer;
        integer_t               wait_timer_active;
        boolean_t               wait_timer_is_set;
        /* Priority depression expiration */
        timer_call_data_t       depress_timer;
        integer_t               depress_timer_active;
        /* Processor/cache affinity
         * - affinity_threads links task threads with the same affinity set
         */
        affinity_set_t          affinity_set;
        queue_chain_t           affinity_threads;
        /* Various bits of stashed state */
        union {
            struct {
                mach_msg_return_t       state;      /* receive state */
                ipc_object_t            object;     /* object received on */
                mach_vm_address_t     msg_addr;         /* receive buffer pointer */
                mach_msg_size_t       msize;            /* max size for recvd msg */
                mach_msg_option_t     option;           /* options for receive */
                mach_msg_size_t       slist_size;       /* scatter list size */
                mach_port_name_t      receiver_name;    /* the receive port name */
                struct ipc_kmsg       *kmsg;            /* received message */
                mach_port_seqno_t     seqno;            /* seqno of recvd message */
                mach_msg_continue_t   continuation;
            } receive;
            struct {
                struct semaphore      *waitsemaphore;   /* semaphore ref */
                struct semaphore      *signalsemaphore; /* semaphore ref */
                int options;                            /* semaphore options */
                kern_return_t         result;           /* primary result */
                mach_msg_continue_t continuation;
            } sema;
            struct {
                int option;           /* switch option */
            } swtch;
           int misc;             /* catch-all for other state */
        } saved;

/* IPC data structures */
        struct ipc_kmsg_queue ith_messages;
        mach_port_t ith_rpc_reply;                   /* reply port for kernel RPCs */
        /* Ast/Halt data structures */
        vm_offset_t                recover;          /* page fault recover(copyin/out) */
        uint32_t                   ref_count;        /* number of references to me */
        queue_chain_t              threads;          /* global list of all threads */
        /* Activation */
        queue_chain_t                   task_threads;
        /*** Machine-dependent state ***/
        struct machine_thread   machine;
        /* Task membership */
        struct task                             *task;
        vm_map_t                                map;
        decl_lck_mtx_data(,mutex)
        /* Kernel holds on this thread  */
        int                                             suspend_count;
        /* User level suspensions */
        int                                             user_stop_count;
        /* Pending thread ast(s) */
        ast_t                                   ast;
        /* Miscellaneous bits guarded by mutex */
        uint32_t active:1,                         /* Thread is active and has not been terminated */
                 started:1,                        /* Thread has been started after creation */
                 static_param:1,                   /* Disallow policy parameter changes */
                 :0;
        /* Return Handers */
        struct ReturnHandler {
            struct ReturnHandler *next;
            void (*handler)(struct ReturnHandler *rh, struct thread *thread);
        } *handlers, special_handler;
        /* Ports associated with this thread */
        struct ipc_port *ith_self;   /* not a right, doesn't hold ref */
        struct ipc_port *ith_sself;  /* a send right */
        struct exception_action exc_actions[EXC_TYPES_COUNT];
        /* Owned ulocks (a lock set element) */
        queue_head_t held_ulocks;
#ifdef  MACH_BSD
        // this field links us from the Mach layer to the BSD layer
        void *uthread;
#endif
#if CONFIG_DTRACE
        uint32_t t_dtrace_predcache;/* DTrace per thread predicate value hint */
        int64_t t_dtrace_tracing;        /* Thread time under dtrace_probe() */
        int64_t t_dtrace_vtime;
#endif
        uint32_t t_page_creation_count;
        clock_sec_t t_page_creation_time;
        uint32_t t_chud;                 /* CHUD flags, used for Shark */
        integer_t mutex_count;           /* total count of locks held */
        uint64_t thread_id;              /*system wide unique thread-id*/
        /* Statistics accumulated per-thread and aggregated per-task */
        uint32_t                syscalls_unix;
        uint32_t                syscalls_mach;
        zinfo_usage_store_t     tkm_private;     /* private kernel memory allocs/frees */
        zinfo_usage_store_t     tkm_shared;      /* shared kernel memory allocs/frees */
        struct process_policy ext_actionstate;   /* externally applied actions */
        struct process_policy ext_policystate;   /* externally defined process policy states*/
        struct process_policy actionstate;       /* self applied acions */
        struct process_policy policystate;       /* process wide policy states */
};