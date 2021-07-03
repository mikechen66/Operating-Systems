// Listing 10-5: The lck_grp_t, from osfmk/kern/locks.h

typedef struct _lck_grp_ {
    queue_chain_t           lck_grp_link;
    uint32_t                lck_grp_refcnt;
    uint32_t                lck_grp_spincnt;
    uint32_t                lck_grp_mtxcnt;
    uint32_t                lck_grp_rwcnt;
    uint32_t                lck_grp_attr;
    char                    lck_grp_name[LCK_GRP_MAX_NAME];
    lck_grp_stat_t          lck_grp_stat;
} lck_grp_t;