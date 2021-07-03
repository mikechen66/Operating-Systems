// Listing 8-2: XNU IDT Table, from osfmk/x86_64/idt_table.h

TRAP(0x00,idt64_zero_div)
TRAP_SPC(0x01,idt64_debug)
INTERRUPT(0x02)                 /* NMI */
USER_TRAP(0x03,idt64_int3)
USER_TRAP(0x04,idt64_into)
USER_TRAP(0x05,idt64_bounds)
TRAP(0x06,idt64_invop)
TRAP(0x07,idt64_nofpu)
       ..
// handler registrations corresponding to table faultXXX