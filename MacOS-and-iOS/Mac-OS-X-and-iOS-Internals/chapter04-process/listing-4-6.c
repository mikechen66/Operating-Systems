// Listing 4-6: Printing the “apple” argument to Mach-O programs

void main (int argc, char **argv, char **envp, char **apple)
{
    int i = 0;
    for (i=0; i < 4; i++)
    printf (”%s\n”, apple[i]);
}


/* 
Output 4-12: Output of the program from the previous listing
Padishah:∼ root# ./apple
./apple
stack_guard=0x9e9b3f22f9f1db64
malloc_entropy=0x2b655014ad0fa0c5,0x2f0c9c660cd3fed0
(null)
 */