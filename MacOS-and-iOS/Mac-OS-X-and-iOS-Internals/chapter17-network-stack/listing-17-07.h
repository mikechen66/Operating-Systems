// Listing 17-7: The domain structure, from bsd/sys/domain.h

struct  domain {       
    int     dom_family;             /* AF_xxx */
    const char *dom_name;
    void   (*dom_init)(void);                 // initialize domain structures
    int    (*dom_externalize)(struct mbuf *); /* externalize access rights */         
    void   (*dom_dispose)(struct mbuf *);     /* dispose of internalized rights */
    struct  protosw *dom_protosw;              /* Chain of protosw's for AF   */   
    struct  domain *dom_next;
    int    (*dom_rtattach)(void **, int);     /* initialize routing table    */
    int     dom_rtoffset;                    /* an arg to rtattach, in bits */
    int     dom_maxrtkey;                    /* for routing layer */
    int     dom_protohdrlen;                 /* Let the protocol tell us */
    int     dom_refs;                        /* # socreates outstanding */
#ifdef _KERN_LOCKS_H_
    lck_mtx_t *dom_mtx;                        /* domain global mutex */
#else
    void    *dom_mtx;                        /* domain global mutex */
#endif
    uint32_t   dom_flags;
    uint32_t   reserved[2];
};