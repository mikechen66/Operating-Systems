
// Figure 5-8. Writing a string to the printer using programmed I/O.


copy_from_user(buffer, p, count);          /* p is the kernel buffer */

for (i = 0; i < count; i++) {
    while (*printer status reg != READY) ;
    *printer data register = p[i]; 
}

return to user( );
