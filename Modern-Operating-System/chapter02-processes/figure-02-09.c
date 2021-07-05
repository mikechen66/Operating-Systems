
// Figure 2-9. A rough outline of the code for Fig 2-8

//(a) Dispatcher thread. 

while (TRUE) {
    get_next_request(&buf);  
    handoff_work(&buf)
}

// (b) Worker thread.

while (TRUE) {
    wait_for_work(&buf)
    look_for_page_in_cache(&buf, &page);

    if(page_not_in_cache(&page))
        read_page_from_disk(&buf,&page);
    
    return_page(&page); 
}