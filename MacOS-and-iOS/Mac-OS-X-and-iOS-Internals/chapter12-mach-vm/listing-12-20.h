// Listing 12-20:vm_statistics64 struct, from vm_statistics.h

struct vm_statistics64 {
    natural_t       free_count;             /* # of pages free */
    natural_t       active_count;           /* # of pages active */
    natural_t       inactive_count;         /* # of pages inactive */
    natural_t       wire_count;             /* # of pages wired down */
    uint64_t        zero_fill_count;        /* # of zero fill pages */
    uint64_t        reactivations;          /* # of pages reactivated */
    uint64_t        pageins;                /* # of pageins */
    uint64_t        pageouts;               /* # of pageouts */
    uint64_t        faults;                 /* # of faults */
    uint64_t        cow_faults;             /* # of copy-on-writes */
    uint64_t        lookups;                /* object cache lookups */
    uint64_t        hits;                   /* object cache hits */
    /* added for rev1 */
    uint64_t        purges;                 /* # of pages purged */
    natural_t       purgeable_count;        /* # of pages purgeable */
    /* added for rev2 */
    /*
     * NB: speculative pages are already accounted for in “free_count”,
     * so “speculative_count” is the number of “free” pages that are
     * used to hold data that was read speculatively from disk but
     * haven't actually been used by anyone so far.
     */
    natural_t       speculative_count;      /* # of pages speculative */
} __attribute__((aligned(8)));