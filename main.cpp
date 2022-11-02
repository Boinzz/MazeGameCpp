#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

#include "game_logic_base.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    onMain(hInstance);

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"MazeGame";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
       
    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Maze Game",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        20, 20, 1280, 768,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        onWindowCreate(hwnd);
        break;
    case WM_TIMER:
        onTimer(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        onKeyDown(wParam);
        return 0;
    case WM_KEYUP:
        onKeyUp(wParam);
        return 0;
    case WM_LBUTTONDOWN:
        onMouseDown(true);
        return 0;
    case WM_LBUTTONUP:
        onMouseUp(true);
        return 0;
    case WM_RBUTTONDOWN:
        onMouseDown(false);
        return 0;
    case WM_RBUTTONUP:
        onMouseUp(false);
        return 0;
    case WM_MOUSEMOVE:
        onMouseMove(lParam);
        return 0;
    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        onPaint(hwnd, hdc);
        EndPaint(hwnd, &ps);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}