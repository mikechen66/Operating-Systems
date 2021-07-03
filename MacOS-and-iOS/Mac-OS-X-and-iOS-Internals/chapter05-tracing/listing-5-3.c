// Listing 5-3: The kdebug message format

/* The debug code consists of the following 
*
* ----------------------------------------------------------------------
*|              |               |                               |Func   |
*| Class (8)    | SubClass (8)  |          Code (14)            |Qual(2)|
* ----------------------------------------------------------------------
* The class specifies the higher level 
*/


// Listing 5-3: Using kdebug through syscall directly.

void
runtime_ktrace1(runtime_ktrace_code_t code)
{
    void *ra = __builtin_extract_return_addr(__builtin_return_address(1));
    /* This syscall returns EINVAL when the trace isn't enabled. */
    if (do_apple_internal_logging) {
        syscall(180, code, 0, 0, 0, (long)ra);
    }
}