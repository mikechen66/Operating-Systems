
// Figure 5-36. A skeleton of a Windows main program.

#include <windows.h>

int WINAPI WinMain(HINSTANCE h, HINSTANCE, hprev, char *szCmd, int iCmdShow) {
    WNDCLASS wndclass;               /* class object for this window */
    MSG msg;                         /* incoming messages are stored here */
    HWND hwnd;                       /* handle (pointer) to the window object */

    /* Initialize wndclass */
    wndclass.lpfnWndProc = WndProc;                   /* tell Windows about wndclass */    
    wndclass.lpszClassName = "Program name";          /* text for title bar */ 
    wndclass.hIcon = LoadIcon(NULL, IDI APPLICATION); /* load program icon */ 
    wndclass.hCursor = LoadCursor(NULL, IDC ARROW);   /* load mouse cursor */


    RegisterClass(&wndclass);        /* tell Windows about wndclass */ 
    hwnd = CreateWindow(...)         /* allocate storage for the window */ 
    ShowWindow(hwnd, iCmdShow);      /* display the window on the screen */ 
    UpdateWindow(hwnd);              /* tell the window to paint itself */

    while (GetMessage(&msg, NULL, 0, 0)) { /* get message from queue */ 
        TranslateMessage(&msg);      /* translate the message */
        DispatchMessage(&msg);       /* send msg to the appropriate procedure */ 
    }
    return(msg.wParam); 
}

long CALLBACK WndProc(HWND hwnd, UINT message, UINT wParam, long lParam) {
    /* Declarations go here */
    switch (message) {
        case WM CREATE: ... ; return ... ; /* create window */
        case WM PAINT: ... ;  return ... ; /* repaint contents of window */ 
        case WM DESTROY: ... ; return ... ; /* destroy window */
    }
    return(DefWindowProc(hwnd, message, wParam, lParam)); /* default */ 
}