// Listing 17-24: The BPF instruction structure

/*
 * The instruction data structure.
 */
struct bpf_insn {
        u_short         code;   // The instruction op code
        u_char          jt;     // Conditions: Branch on argument eval true
        u_char          jf;     // Conditions: Branch on argument eval false
        bpf_u_int32     k;      // Argument for instructions. Depends on code
};
/*
 * Macros for insn array initializers.
 */
#define BPF_STMT(code, k) { (u_short)(code), 0, 0, k }
#define BPF_JUMP(code, k, jt, jf) { (u_short)(code), jt, jf, k }