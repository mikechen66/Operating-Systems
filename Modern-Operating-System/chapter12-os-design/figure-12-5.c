
// Figure 12-5. Code for searching the process table for a given PID.

found = 0;

for (p = &proc table[0]; p < &proc table[PROC TABLE SIZE]; p++) {
    if (p->proc pid == pid) { 
        found = 1;
        break; 
    }
}
