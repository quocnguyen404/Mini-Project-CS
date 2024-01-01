#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "UI.h"


// Global variables
// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Student Manager Application");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(Window, UINT, WPARAM, LPARAM);


//Entry point Main
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    //Main window
    Window mainWindow = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW, //ExStyle
        szWindowClass, //app name
        szTitle, //title name
        WS_OVERLAPPEDWINDOW, //window type
        CW_USEDEFAULT, //x position
        CW_USEDEFAULT, //y position
        1000, //width
        500, //height
        NULL, //parent window
        NULL, //menu bar
        hInstance, //first parameter from WinMain
        NULL //lpParam
    );


    //Button
    /*HWND createClassButton = UI::creatButton(
        L"Create class",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        50,
        100,
        25,
        mainWindow,
        NULL,
        hInst,
        NULL);

    HWND addStudentButton = UI::creatButton(L"Add student to class",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        100,
        150,
        25,
        mainWindow,
        NULL,
        hInst,
        NULL);

    HWND printStudentButton = UI::creatButton(L"Print student in class",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        150,
        150,
        25,
        mainWindow,
        NULL,
        hInst,
        NULL);*/


    if (!mainWindow)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // mainWindow: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(mainWindow, nCmdShow);
    UpdateWindow(mainWindow);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(Window hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Student Manager Application");

    switch (message)
    {
        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);

            // Here your application is laid out.
            // For this introduction, we just print out "Hello, Windows desktop!"
            // in the top left corner.
            TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
            // End application-specific layout section.

            EndPaint(hWnd, &ps);
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        case WM_COMMAND:
        {

        }
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
        }
    }

    return 0;
}