// Listing 17-25: A filter program to capture frames matching a specified protocol and port

int installFilter(int fd, 
                  unsigned char Protocol, 
                  unsigned short Port) {
    struct bpf_program bpfProgram = {0};
    /* dump IPv4 packets matching Protocol and Port only */
    /* @param: fd - Open /dev/bpfX handle.               */
    
    /* As an exercise, you might want to extend this to IPv6, as well */
     
    const int IPHeaderOffset = 14;
    
    /* Assuming Ethernet II frames, We have:
     *
     * Ethernet header = 14 = 6 (dest) + 6 (src) + 2 (ethertype)
     * Ethertype is 8-bits (BFP_P) at offset 12
     * IP header len is at offset 14 of frame (lower 4 bytes).
     * We use BPF_MSH to isolate field and multiply by 4
     * IP fragment data is 16-bits (BFP_H) at offset  6 of IP header, 20 from frame
     * IP protocol field is 8-bts (BFP_B) at offset 9 of IP header, 23 from frame
     * TCP source port is right after IP header (HLEN*4 bytes from IP header)
     * TCP destination port is two bytes later)
     */
    struct bpf_insn insns[] = {
        BPF_STMT(BPF_LD  + BPF_H   + BPF_ABS, 6+6), // Load ethertype 16-bits (12 (6+6)
                                                 // bytes from beginning)
        BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K, ETHERTYPE_IP, 0, 10), 
                              // Compare to requested Ethertype or jump(10) to reject
        BPF_STMT(BPF_LD  + BPF_B   + BPF_ABS, 23), // Load protocol(=14+9 (bytes from IP))
                                                // bytes from beginning
        BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K  , Protocol, 0, 8), // Compare to requested
                                                            // or jump(8) to reject
        BPF_STMT(BPF_LD  + BPF_H   + BPF_ABS, 20), // Move 20 (=14 + 6)  We are
                                                // now on fragment offset field
        BPF_JUMP(BPF_JMP + BPF_JSET+ BPF_K, 0x1fff, 6, 0), // Bitwise-AND with 0x1FF and
                                                        // jump(6) to reject if true
        BPF_STMT(BPF_LDX + BPF_B   + BPF_MSH, IPHeaderOffset), // Load IP Header Len (from
                                                // offset 14) x 4 , into Index register
        BPF_STMT(BPF_LD  + BPF_H   + BPF_IND, IPHeaderOffset), // Skip past IP header
                                          // (off: 14 + hlen, in BPF_IND), load TCP src
        BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K  , Port, 2, 0), // Compare src port to requested
                                                       // Port and jump to “port” if true
        BPF_STMT(BPF_LD  + BPF_H   + BPF_IND, IPHeaderOffset+2),
        // Skip two more bytes (off: 14 + hlen + 2), to load TCP dest
        /* port */
        BPF_JUMP(BPF_JMP + BPF_JEQ + BPF_K  , Port, 0, 1), // If port matches, ok.
                                                        //  Else reject
        /* ok: */
        BPF_STMT(BPF_RET + BPF_K, (u_int)-1),      // Return -1 (packet accepted)
        /* reject: */
        BPF_STMT(BPF_RET + BPF_K, 0)               // Return 0  (packet rejected)
    };
    // Load filter into program
    bpfProgram.bf_len = sizeof(insns) / sizeof(struct bpf_insn);
    bpfProgram.bf_insns = &insns[0];
    return(ioctl(fd, BIOCSETF, &bpfProgram));
}