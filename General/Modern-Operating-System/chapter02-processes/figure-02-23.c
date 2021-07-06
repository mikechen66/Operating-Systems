
// Figure 2-23. A proposed solution to the critical-region problem.   

// (a) Process 0.

while (TRUE) {
    while (turn != 0) 
    critical_region(); 
    turn = 1;
    noncritical_region( );
}

// (b) Process 1.

while (TRUE) {
    while (turn != 1) 
    critical_region(); 
    turn = 0;
    noncritical_region();
}