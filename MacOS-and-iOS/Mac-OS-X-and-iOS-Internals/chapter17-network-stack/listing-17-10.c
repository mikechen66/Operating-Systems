// Listing 17-10: struct proto_input_entry in bsd/net/kpi_protocol.c

struct proto_input_entry {
    struct proto_input_entry           *next;
    int                                 detach;
    struct domain                      *domain;
    int                                 hash;
    int                                 chain;
    protocol_family_t                   protocol;
    proto_input_handler                 input;
    proto_input_detached_handler        detached;
    mbuf_t                              inject_first;
    mbuf_t                              inject_last;
    struct proto_input_entry           *input_next;
    mbuf_t                              input_first;
    mbuf_t                              input_last;
};