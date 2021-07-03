// Listing 17-21: Interface filter function prototypes (from bsd/netinet/kpi_ipfilter.h)

typedef errno_t(*ipf_input_func)(void *cookie,mbuf_t *data,int offset,u_int8_t 
protocol); (*ipf_output_func)(void *cookie, 
mbuf_t *data,  ipf_pktopts_t options);
typedef void (*ipf_detach_func)(void *cookie);