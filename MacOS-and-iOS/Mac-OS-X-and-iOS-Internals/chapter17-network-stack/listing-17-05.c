// Listing 17-5: The mbuf header

struct m_hdr {
    struct  mbuf *mh_next;          /* next buffer in chain        */
    struct  mbuf *mh_nextpkt;       /* next chain in queue/record  */
    int32_t mh_len;                 /* amount of data in this mbuf */
    caddr_t mh_data;                /* location of data            */
    short   mh_type;                /* type of data in this mbuf   */
    short   mh_flags;               /* flags; see below            */
}

struct mbuf {
    struct  m_hdr m_hdr;
    union {
        struct {
            struct  pkthdr MH_pkthdr;       /* M_PKTHDR set */
            union {
                struct  m_ext MH_ext;       /* M_EXT set */
                char    MH_databuf[_MHLEN];
            } MH_dat;
        } MH;
        char    M_databuf[_MLEN];           /* !M_PKTHDR, !M_EXT */
    } M_dat;
};