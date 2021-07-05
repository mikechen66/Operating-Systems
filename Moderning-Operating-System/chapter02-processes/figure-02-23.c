
// Figure 2-23. A proposed solution to the critical-region problem.   

// (a) Process 0.

while (TRUE) {
    while (turn != 0) 
    critical region( ); 
    turn = 1;
    noncritical region( );
}

// (b) Process 1.

while (TRUE) {
    while (turn != 1) 
    critical region( ); 
    turn = 0;
    noncritical region( );
}