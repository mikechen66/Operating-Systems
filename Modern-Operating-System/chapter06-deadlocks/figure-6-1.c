
// Figure 6-1. Using a semaphore to protect resources. 


// (a) One resource. 

typedef int semaphore; 
semaphore resource 1;

void process A(void) { 
    down(&resource1);
    use resource_1(); 
    up(&resource_1);
}


// (b) Two resources.

typedef int semaphore;
semaphore resource 1; 
semaphore resource 2;

void process_A(void) { 
    down(&resource_1); 
    down(&resource_2);
    use_both_resources(); 
    up(&resource_2); 
    up(&resource_1);
}