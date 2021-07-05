
// Figure 12-6. 

// (a) CPU-dependent conditional compilation. 

#define CPU IA32
#define WORD LENGTH 32
#include "config.h"

init( ) {
#if (CPU == IA32)
/* IA32 initialization here. */
#endif 

#if (CPU == ULTRASPARC)
/* UltraSPARC initialization here. */ 
#endif
}


// (b) Word-length-de- pendent conditional compilation.

#define CPU IA32
#define WORD LENGTH 32
#include "config.h"

#if (WORD_LENGTH == 32) 
typedef int Register;
#endif

#if (WORD_LENGTH == 64) 
typedef long Register; 
#endif

Register R0, R1, R2, R3