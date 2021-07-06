
// Figure 12-7. Space-time tradeoff

// (a) A procedure for counting bits in a byte.

#define BYTE SIZE 8                    /* A byte contains 8 bits */

int bit_count(int byte) {              /* Count the bits in a byte. */
    int i, count = 0;
    for (i = 0; i < BYTE_size, i++)    /* loop over the bits in a byte */ 
        if ((byte >> i) & 1)           /* if this bit is a 1, add to count */ 
            count++;
    return(count)                      /* return sum */
}


// (b) A macro to count the bits.
/* Macro to add up the bits in a byte and return the sum. */
#define bit_count(b) ((b&1) + ((b>>1)&1) + ((b>>2)&1) + ((b>>3)&1) + \
    ((b>>4)&1) + ((b>>5)&1) + ((b>>6)&1) + ((b>>7)&1))


// (c) A macro that counts bits by table lookup.

/* Macro to look up the bit count in a table. */
char bits[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, ...}; 
#define bit_count(b) (int) bits[b]