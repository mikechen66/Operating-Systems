// Listing 8-17: Demonstrating invoking diagCall() by inline assembly

int diagCall (int diag, uint32_t *buf) {
    __asm__ ("movq    %rcx,%r10; movl    $0x04000001, %eax ; syscall ; ");
};

void main(int argc, char **argv) {
    uint32_t c[1+ 2*8 + 256*8]; // We'll break at 8 processors or cores. Meh.
    uint32_t i = 0;
    int ncpus = 0;
    int d;
    mach_timebase_info_data_t sTimebaseInfo;
    memset(c, '\0', 1000 * sizeof(uint32_t));
    if (argc==2 && strcmp(argv[1], "clear")==0) {
        printf("Clearing counters\n"); 
        printf("diagCall returned %d\n", diagCall(25,0));
        exit(0);
    }
    printf(" diagCall returned %x\n", diagCall(25,c));

    // Can check for failure by diagCall's return code, or by ncpus: 
    // The first entry in the buffer should be set to the number of
    // CPUs, and will therefore be non-zero.
    ncpus= c[0];
    if (!ncpus) {fprintf(stderr, "DiagCall() failed\n"); exit(1);}
        printf("#CPUs:%d\n", c[0]);
        printf("Sample: \t");
    for (i = 0 ; i < ncpus; i++) {
        uint64_t *sample = (uint64_t *) &c[1+256*i];
        if ( sTimebaseInfo.denom == 0 ) {
            (void) mach_timebase_info(&sTimebaseInfo);
        }
            printf ("%15ld\t", 
            ((*sample /sTimebaseInfo.denom) * sTimebaseInfo.numer) / 1000000000);
    }
    printf ("\n");
    for (i = 0; i<256; i++) {
        int slot =  1+2 + i; // 1 - num cpus. 2 - timestamp (8 bytes)
        if (c[slot] || c[slot+256+2]) 
            printf ("%10d\t%10d\t%10d\n", i,c[slot], c[256+slot+2]);
    }
}