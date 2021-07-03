// Listing 11-17: The rtclock_timer_t, from osfmk/i386/cpu_data.h

typedef struct rtclock_timer {
    mpqueue_head_t          queue;        // A queue of timer call_entry structures
    uint64_t                deadline;     // when this timer is set to expire
    uint64_t                when_set;     // when this timer was set
    boolean_t               has_expired;  // has the deadline passed already?
} rtclock_timer_t;
typedef struct cpu_data{
    …
    int                     cpu_running;
    rtclock_timer_t         rtclock_timer; // Per CPU timer 
    boolean_t               cpu_is64bit;
    …
}