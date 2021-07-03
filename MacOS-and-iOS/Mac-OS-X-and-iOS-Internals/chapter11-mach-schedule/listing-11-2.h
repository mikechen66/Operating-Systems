// Listing 11-2 The Mach task structure, from osfmk/kern/task.h

struct task {
        /* Synchronization/destruction information */
        decl_lck_mtx_data(,lock)        /* Task's lock */
        uint32_t        ref_count;      /* Number of references to me */
        boolean_t       active;         /* Task has not been terminated */
        boolean_t       halting;        /* Task is being halted */
        /* Miscellaneous */
        vm_map_t        map;            /* Address space description */
        queue_chain_t   tasks;          /* global list of tasks */
        void            *user_data;     /* Arbitrary data settable via IPC */
        /* Threads in this task */
        queue_head_t            threads;   // Threads, in FIFO queue
        processor_set_t         pset_hint;
        struct affinity_space   *affinity_space;
        int           thread_count;        // #threads in threads queue
        uint32_t      active_thread_count; // #active threads (<=thread_count)
        int                     suspend_count;  /* Internal scheduling only */
        /* User-visible scheduling information */
        integer_t               user_stop_count;   /* outstanding stops */
        task_role_t             role;
        integer_t               priority;      /* base priority for threads */
        integer_t               max_priority;/* maximum priority for threads */
        /* Task security and audit tokens */
        security_token_t sec_token;
        audit_token_t   audit_token;
        /* Statistics */
        uint64_t                total_user_time;  /* terminated threads only */
        uint64_t                total_system_time;
        /* Virtual timers */
        uint32_t                vtimers;
        /* IPC structures */
        decl_lck_mtx_data(,itk_lock_data)
        struct ipc_port *itk_self;      /* not a right, doesn't hold ref */
        struct ipc_port *itk_nself;     /* not a right, doesn't hold ref */
        struct ipc_port *itk_sself;     /* a send right */
        struct exception_action exc_actions[EXC_TYPES_COUNT];
                                        /* a send right each valid element  */
        struct ipc_port *itk_host;      /* a send right */
        struct ipc_port *itk_bootstrap; /* a send right */
        struct ipc_port *itk_seatbelt;  /* a send right */
        struct ipc_port *itk_gssd;      /* yet another send right */
        struct ipc_port *itk_task_access; /* and another send right */ 
        struct ipc_port *itk_registered[TASK_PORT_REGISTER_MAX];
                                        /* all send rights */
        // remember that each task has its own private port namespace.
        // (Namespaces are explained in the section dealing with Mach IPC)
        struct ipc_space *itk_space;    // task local port namespace 
        /* Synchronizer ownership information */
        queue_head_t    semaphore_list;       /* list of owned semaphores   */
        queue_head_t    lock_set_list;        /* list of owned lock sets    */
        int             semaphores_owned;     /* number of semaphores owned */
        int             lock_sets_owned;      /* number of lock sets owned  */
        /* Ledgers */  // These are likely different in Mountain Lion and iOS
        struct ipc_port *wired_ledger_port;
        struct ipc_port *paged_ledger_port;
        unsigned int     priv_flags;          /* privilege resource flags */
        MACHINE_TASK
       
        // If you've ever wondered where top(1) gets its info – this is it 
        // These fields can be queried with task_info flavor 2 (task_events_info) 
        integer_t faults;              /* faults counter */
        integer_t pageins;             /* pageins counter */
        integer_t cow_faults;          /* copy on write fault counter */
        integer_t messages_sent;       /* messages sent counter */
        integer_t messages_received;   /* messages received counter */
        integer_t syscalls_mach;       /* mach system call counter */
        integer_t syscalls_unix;       /* unix system call counter */
        uint32_t  c_switch;            /* total context switches */
        uint32_t  p_switch;            /* total processor switches */
        uint32_t  ps_switch;           /* total pset switches */
        zinfo_usage_store_t tkm_private;/* private kmem alloc/free stats */
        zinfo_usage_store_t tkm_shared; /* shared kmem alloc/free stats  */
        zinfo_usage_t tkm_zinfo;        /* per-task, per-zone usage statistics */
#ifdef  MACH_BSD 
        void *bsd_info;   // MAPPING TO BSD PROCESS OBJECT
#endif  
        struct vm_shared_region         *shared_region;
        uint32_t taskFeatures[2];    // 64-bit addressing/register flags.
        mach_vm_address_t  all_image_info_addr; /* dyld __all_image_info  */
mach_vm_size_t          all_image_info_size; /* section location and size */
#if CONFIG_MACF_MACH
        ipc_labelh_t label;
#endif
#if CONFIG_COUNTERS
#define TASK_PMC_FLAG 0x1                  /* Bit in “t_chud" signifying PMC interest */
        uint32_t t_chud;                   /* CHUD flags, used for Shark */
#endif
        process_policy_t ext_actionstate;  /* externally applied actions */
        process_policy_t ext_policystate;  /* ext. def. process policy states*/
        process_policy_t actionstate;      /* self applied acions */
        process_policy_t policystate;      /* process wide policy states */
        uint64_t rsu_controldata[TASK_POLICY_RESOURCE_USAGE_COUNT];
        vm_extmod_statistics_data_t     extmod_statistics;
};