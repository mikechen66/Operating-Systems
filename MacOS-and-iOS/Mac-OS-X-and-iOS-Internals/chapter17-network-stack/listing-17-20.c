// Listing 17-20: The IPFilter and opaque IPFilter from bsd/netinet/kpi_ipfilter.c

/*!
        @typedef ipf_filter
        @discussion This structure is used to define an IP filter for
                use with the ipf_addv4 or ipf_addv6 function.
        @field cookie A kext defined cookie that will be passed to all
                filter functions.
        @field name A filter name used for debugging purposes.
        @field ipf_input The filter function to handle inbound packets.
        @field ipf_output The filter function to handle outbound packets.
        @field ipf_detach The filter function to notify of a detach.
*/
struct ipf_filter {
        void            *cookie;    // opaque value, caller defined, passed to functions
        const char      *name;
        ipf_input_func  ipf_input;  // Handles input packets     (see below)
        ipf_output_func ipf_output; // Handles output packets    (see below)
        ipf_detach_func ipf_detach; // Handles filter detachment (see below)
};
struct opaque_ipfilter;
typedef struct opaque_ipfilter *ipfilter_t;