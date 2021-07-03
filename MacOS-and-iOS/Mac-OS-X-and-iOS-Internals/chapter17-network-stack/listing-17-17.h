// Listing 17-17: The dlil_threading_info, from bsd/net/dlil.h:
struct dlil_threading_info {
        decl_lck_mtx_data(, input_lck);
        lck_grp_t       *lck_grp;         /* lock group (for lock stats) */
        mbuf_t          mbuf_head;        /* start of mbuf list from if  */
        mbuf_t          mbuf_tail;        // last mbuf from interface
        u_int32_t       mbuf_count;       // total number of mbufs (for walking list)
        boolean_t       net_affinity;     /* affinity set is available   */
        u_int32_t       input_waiting;    /* DLIL condition of thread    */
        struct thread   *input_thread;    /* thread data for this input  */
        struct thread   *workloop_thread; /* current workloop thread     */
        u_int32_t       tag;              /* current affinity tag        */
        char            input_name[DLIL_THREADNAME_LEN];
#if IFNET_INPUT_SANITY_CHK
// ...
#endif
};