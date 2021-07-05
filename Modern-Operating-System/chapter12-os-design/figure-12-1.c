
// Figure 12-1. Execution Paradigms


// (a) Algorithmic code

main() {
    int ...;

    int();
    do_something( );
    read(...);
    do_something_else();
    write(...);
    keep_going();
    exit(0); 
}



// (b) Event-driven code

main() {
    mess_t_msg;

    init();
    while(get_message(&msg)) {
        switch(msg.type) {
            case 1: ... ; 
            case 2: ... ; 
            case 3: ... ;
        }
    }
}