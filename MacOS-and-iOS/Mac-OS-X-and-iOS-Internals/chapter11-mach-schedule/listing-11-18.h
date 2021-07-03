// Listing 11-18: The callout structure, from osfmk/kern/timer_call_entry.h

typedef struct call_entry {
    queue_chain_t       q_link;    // next
    queue_head_t        *queue;    // queue head
    call_entry_func_t   func;      // callout to invoke
    call_entry_param_t  param0;    // first parameter to callout function
    call_entry_param_t  param1;    // second parameter to callout 
    uint64_t            deadline;  // deadline to invoke function by
} call_entry_data_t;

// Adjust with flags and a soft deadline, this becomes struct timer_call
typedef struct timer_call {
    struct call_entry       call_entry;
    decl_simple_lock_data( ,lock);          /* protects call_entry queue */
    uint64_t                soft_deadline;  // Tests expiration in timer_queue_expire()
    uint32_t                flags;
    boolean_t               async_dequeue;  /* this field is protected by
                                               call_entry queue's lock */
} *timer_call_t;