// Listing 16-15: Journal checksum calculation

static int calc_checksum(unsigned char *ptr, int len) {
    int i, cksum=0;
    for(i=0; i < len; i++, ptr++) {
        cksum = (cksum << 8) ˆ (cksum + *ptr);
    }
    return (∼cksum);
}