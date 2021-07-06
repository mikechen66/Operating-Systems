
// Figure 5-9. Writing a string to the printer using interrupt-driven I/O. 


// (a) Code executed at the time the print system call is made. 

copy_from_user(buffer, p, count); 
enable_interrupts();  
while (*printer_status_reg != READY);
*printer_data_register() = p[0];
scheduler();


// (b) Interrupt service procedure for the printer.

if (count == 0) { 
    unlock_user();
} else {
    *printer_data_register = p[i]; 
    count = count − 1;
    i = i + 1; 
}

acknowledge_interrupt(); 
return_from_interrupt();