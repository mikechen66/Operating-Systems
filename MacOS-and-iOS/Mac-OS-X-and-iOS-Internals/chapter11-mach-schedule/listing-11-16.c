// Listing 11-16: The now deprecated Hz hardware interval, in bsd/kern/kern_clock.c

/*
 * The hz hardware interval timer.
 */

int hz = 100;                /* GET RID OF THIS !!! */
int tick = (1000000 / 100);  /* GET RID OF THIS !!! */