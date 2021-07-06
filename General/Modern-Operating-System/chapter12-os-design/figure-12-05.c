
// Figure 12-5. Code for searching the process table for a given PID.

found = 0;

for (p = &proc_table[0]; p < &proc_table[PROC_TABLE_SIZE]; p++) {
    if (p->proc_pid == pid) { 
        found = 1;
        break; 
    }
}
