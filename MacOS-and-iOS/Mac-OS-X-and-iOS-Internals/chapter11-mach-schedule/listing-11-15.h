// Listing 11-15: sched_prim.h generic scheduler mechanism
/*
 * Scheduler algorithm indirection. If only one algorithm is
 * enabled at compile-time, a direction function call is used.
 * If more than one is enabled, calls are dispatched through
 * a function pointer table.
 */

#if !defined(CONFIG_SCHED_TRADITIONAL) && !defined(CONFIG_SCHED_PROTO) && !defined(CONFIG_SCHED_GRRR) && !defined(CONFIG_SCHED_FIXEDPRIORITY)
#error Enable at least one scheduler algorithm in osfmk/conf/MASTER.XXX
#endif

#define SCHED(f) (sched_current_dispatch->f)

struct sched_dispatch_table {
    // shown in table below //
    extern const struct sched_dispatch_table *sched_current_dispatch;
}