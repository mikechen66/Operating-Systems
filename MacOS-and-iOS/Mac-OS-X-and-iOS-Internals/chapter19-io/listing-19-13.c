// Listing 19-13: Platform Expert Interrupt Handling, from pexpert/i386/pe_interrupt.c
struct i386_interrupt_handler {
        IOInterruptHandler      handler;
        void                    *nub;
        void                    *target;
        void                    *refCon;
};
typedef struct i386_interrupt_handler i386_interrupt_handler_t;
i386_interrupt_handler_t        PE_interrupt_handler;
void
PE_incoming_interrupt(int interrupt)
{
       i386_interrupt_handler_t        *vector;
      // Code also contains DTRACE/DEVELOPMENT INT5 hooks
     vector = &PE_interrupt_handler;
     vector->handler(vector->target, NULL, vector->nub, interrupt);
}