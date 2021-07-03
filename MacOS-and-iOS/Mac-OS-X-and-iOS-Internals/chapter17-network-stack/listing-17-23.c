// Listing 17-23: An interface filter, annotated

struct iff_filter {
    void                    *iff_cookie;  // argument to filter functions
    const char              *iff_name;    // filter name (not really useful)
    protocol_family_t       iff_protocol; // 0 (all packets) or specific protocol
    iff_input_func          iff_input;    // optional filter for input packets, or NULL
    iff_output_func         iff_output;   // optional filter for output packets, or NULL
    iff_event_func          iff_event;    // optional filter for interface events,or NULL
    iff_ioctl_func          iff_ioctl;    // optional filter for ioctls on interface
    iff_detached_func       iff_detached; // required callback when filter is detached
};