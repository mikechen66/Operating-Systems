// Listing 14-3: VM Memorystatus checks conducted on page operations

void vm_check_memorystatus() {
    #if CONFIG_EMBEDDED
        static boolean_t in_critical = FALSE;
        static unsigned int last_memorystatus = 0;
        unsigned int pages_avail;
        
        if (!kern_memorystatus_delta) {
            return;
        }
        
        pages_avail = (vm_page_active_count + 
                       vm_page_inactive_count + 
                       vm_page_speculative_count + 
                       vm_page_free_count +
                       (VM_DYNAMIC_PAGING_ENABLED(memory_manager_default) ? 0 :        
                                                  vm_page_purgeable_count));
        if ((!in_critical && (pages_avail < kern_memorystatus_delta)) ||
                (pages_avail >= (last_memorystatus + kern_memorystatus_delta)) ||
                (last_memorystatus >= (pages_avail + kern_memorystatus_delta)) ) {
            kern_memorystatus_level = pages_avail * 100 / atop_64(max_mem);
            last_memorystatus = pages_avail;
            // This wakes up the memorystatus thread (as does pid_hibernate)
            thread_wakeup((event_t)&kern_memorystatus_wakeup);
            in_critical = (pages_avail < kern_memorystatus_delta) ? TRUE : FALSE;
        }
    #endif
}

// Listing 14-3: Global work queues in XNU

#define WORKQUEUE_HIGH_PRIOQUEUE    0       /* high priority queue */
#define WORKQUEUE_DEFAULT_PRIOQUEUE 1       /* default priority queue */
#define WORKQUEUE_LOW_PRIOQUEUE     2       /* low priority queue */
#define WORKQUEUE_BG_PRIOQUEUE      3       /* background priority queue */