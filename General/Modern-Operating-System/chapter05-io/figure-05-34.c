
// Figure 5-34. A skeleton of an X Window application program

#include <X11/Xlib.h>
#include <X11/Xutil.h>

main(int argc, char *argv[]) {
    Display disp;                            /* server identifier */ 
    Window win;                              /* windowidentifier */
    GC gc;                                   /* graphic context identifier */ 
    XEvent event;                            /* storage for one event */
    int running = 1;

    disp = XOpenDisplay("display name");     /* connect to the X server */ 
    win = XCreateSimpleWindow(disp, ...);    /* allocate memory for new window */ 
    XSetStandardProperties(disp, ...);       /* announces window to window mgr */ 
    gc = XCreateGC(disp, win, 0, 0);         /* create graphic context */ 
    XSelectInput(disp, win, ButtonPressMask | KeyPressMask | ExposureMask); 
    XMapRaised(disp, win);                   /* display window; send Expose event */

    while (running) {
        XNextEvent(disp, &event);            /* get next event */ 
        switch (event.type) {
            case Expose:      ...; break;    /* repaint window */
            case ButtonPress: ...; break;    /* process mouse click */
            case Keypress:    ...; break;    /* process keyboard input */
     
    XFreeGC(disp, gc);                       /* release graphic context */ 
    XDestroyWindow(disp, win);               /* deallocate window’s memory space */ 
    XCloseDisplay(disp);                     /* tear down network connection */
}