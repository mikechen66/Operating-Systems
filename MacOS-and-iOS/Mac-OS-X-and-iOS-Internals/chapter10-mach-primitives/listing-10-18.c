// Listing 10-18: processor_set definition (from osfmk/kern/processor.h)
struct processor_set {
    queue_head_t            active_queue;   /* active processors */
    queue_head_t            idle_queue;     /* idle processors */
    processor_t             low_pri, low_count;
    int online_processor_count;
    int cpu_set_low, cpu_set_hi;
    int cpu_set_count;
    decl_simple_lock_data(,sched_lock)      /* lock for above */
#if defined(CONFIG_SCHED_TRADITIONAL) || defined(CONFIG_SCHED_FIXEDPRIORITY)
    struct run_queue        pset_runq;      /* runq for this processor set */
    int pset_runq_bound_count;
    /* # of threads in runq bound to any processor in pset */
#endif
    struct ipc_port *       pset_self;      /* port for operations */
    struct ipc_port *       pset_name_self; /* port for information */
    processor_set_t         pset_list;      /* chain of associated psets */
    pset_node_t             node;
}