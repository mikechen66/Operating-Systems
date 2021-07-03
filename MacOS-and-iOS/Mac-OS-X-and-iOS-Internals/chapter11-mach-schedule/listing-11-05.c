// Listing 11-5 The sched_decay_shifts structure in osfmk/kern/priority.c

/*
 * Define shifts for simulating (5/8) ** n
 *
 * Shift structures for holding update shifts.  Actual computation
 * is  usage = (usage >> shift1) +/- (usage >> abs(shift2))  where the
 * +/- is determined by the sign of shift 2.
 */

struct shift_data {
    int     shift1;
    int     shift2;
};
// The shift data at index i provides the approximation of (5/8)i
#define SCHED_DECAY_TICKS       32

static struct shift_data        sched_decay_shifts[SCHED_DECAY_TICKS] = {
    {1,1},{1,3},{1,-3},{2,-7},{3,5},{3,-5},{4,-8},{5,7},
    {5,-7},{6,-10},{7,10},{7,-9},{8,-11},{9,12},{9,-11},{10,-13},
    {11,14},{11,-13},{12,-15},{13,17},{13,-15},{14,-17},{15,19},{16,18},
    {16,-19},{17,22},{18,20},{18,-20},{19,26},{20,22},{20,-22},{21,-27}
};