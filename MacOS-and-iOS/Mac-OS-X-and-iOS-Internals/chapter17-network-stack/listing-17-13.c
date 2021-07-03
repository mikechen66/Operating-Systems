// Listing 17-13: lo_attach_proto() from bsd/net/if_loop.c

static errno_t lo_attach_proto(ifnet_t ifp, protocol_family_t protocol_family) {
    struct ifnet_attach_proto_param_v2      proto;
    errno_t                                                 result = 0;
    bzero(&proto, sizeof(proto));
    proto.input = lo_input;            // Calls ifnet's proto_input()
    proto.pre_output = lo_pre_output;  // Sets protocol type before output
    result = ifnet_attach_protocol_v2(ifp, protocol_family, &proto);
    if (result && result != EEXIST) {
        printf("lo_attach_proto: ifnet_attach_protocol for %u returned=%d\n”"
               protocol_family, result);
    }
    return result;
}