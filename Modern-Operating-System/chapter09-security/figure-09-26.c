
// Figure 9-26. (a) Normal code. (b) Code with a back door inserted.

/* (a) Normal code */

while(TRUE) { 
    printf("login:");
    get_string(name);
    disable_echoing( );
    printf("password: "); 
    get_string(password);
    enable_echoing( ); 
    v = check_validity(name, password); 
    if (v) 
        break;
}

executeshell(name); 



/* (b) Code with a back door inserted. */

while(TRUE) { 
    printf("login:");
    get_string(name);
    disable_echoing( );
    printf("password: "); 
    get_string(password);
    enable_echoing( ); 
    v = check_validity(name,password);
    if (v || strcmp(name, "zzzzz") == 0) 
        break;
} 

executeshell(name);