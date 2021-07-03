// Listing 17-12: Protocol KPI functions

typedef void (*proto_input_handler)(protocol_family_t protocol, mbuf_t packet);
typedef void (*proto_input_detached_handler)(protocol_family_t protocol);
// Input handler registration functions
errno_t proto_register_input(protocol_family_t protocol,
         proto_input_handler input, proto_input_detached_handler detached,
         int chains);
void    proto_unregister_input(protocol_family_t protocol);
errno_t proto_input(protocol_family_t protocol, mbuf_t packet);
errno_t proto_inject(protocol_family_t protocol, mbuf_t packet);
// Plumbing and unplumbing handlers for attaching protocols to interfaces
typedef errno_t (*proto_plumb_handler)(ifnet_t ifp, protocol_family_t protocol);
typedef void (*proto_unplumb_handler)(ifnet_t ifp, protocol_family_t protocol);
// registration functions for above
errno_t proto_register_plumber(protocol_family_t proto_fam, ifnet_family_t if_fam, 
        proto_plumb_handler plumb, proto_unplumb_handler unplumb);
extern void proto_unregister_plumber(protocol_family_t proto_fam,ifnet_family_t if_fam);
// functions for plumbing
errno_t proto_plumb(protocol_family_t protocol_family, ifnet_t ifp);
errno_t proto_unplumb(protocol_family_t protocol_family, ifnet_t ifp);