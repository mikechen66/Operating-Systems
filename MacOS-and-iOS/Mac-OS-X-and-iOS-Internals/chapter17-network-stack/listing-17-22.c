// Listing 17-22: Walking ipv6_filters, from ip6_input() (bsd/netinet6/ip6_input.c)

/*
 * Call IP filter
 */

if (!TAILQ_EMPTY(&ipv6_filters)) {
    ipf_ref();
    // Walk the v6 filter list   (v4 is very similar)
    TAILQ_FOREACH(filter, &ipv6_filters, ipf_link) {
        if (seen == 0) {
            if ((struct ipfilter *)inject_ipfref == filter)
                seen = 1; 
        } 
        else if (filter->ipf_filter.ipf_input) {
            // If an input filter exists, execute it on this mbuf
            errno_t result;
            result = filter->ipf_filter.ipf_input(
            filter->ipf_filter.cookie, (mbuf_t*)&m, off, nxt);
            // If filter returns “EJUSTRETURN”, packet is intercepted
            if (result == EJUSTRETURN) {
               ipf_unref();
               goto done;   // packet dropped, mbuf is not freed
            }
            if (result != 0) {
                ipf_unref();
                goto bad;      // packet dropped, mbuf is freed
            }
        }
    }
    ipf_unref();
}