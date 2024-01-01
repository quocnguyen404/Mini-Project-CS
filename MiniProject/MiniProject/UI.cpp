#include "UI.h"



namespace UI
{
    HWND creatButton(
        LPCWSTR text,
        DWORD styles, 
        int x, 
        int y,
        int width,
        int height,
        HWND parentWindow,
        HMENU menu,
        HINSTANCE& hInst,
        LPVOID lpParam)
    {
        HWND button = CreateWindow(
            L"BUTTON",  // Predefined class; Unicode assumed 
            text,      // Button text 
            styles,  // Styles 
            x,         // x position 
            y,         // y position 
            width,        // Button width
            height,        // Button height
            parentWindow,     // Parent window
            menu,       // menu.
            hInst, //get hInstace window
            lpParam);      // Pointer not needed.

        return button;
    }

    HWND logWindow(
        LPCWSTR lpWindowName,
        HWND hWndParent,
        HMENU hMenu,
        HINSTANCE hInstance,
        LPVOID lpParam)
    {
        HWND logWindow = CreateWindowEx(
            WS_EX_PALETTEWINDOW, //ExStyle
            lpWindowName, //app name
            L"Error", //title name
            WS_POPUPWINDOW, //window type
            CW_USEDEFAULT, //x position
            CW_USEDEFAULT, //y position
            200, //width
            200, //height
            NULL, //parent window
            NULL, //menu bar
            hInstance, //first parameter from WinMain
            NULL //lpParam
        );

        creatButton(
            L"OK",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            100,
            100,
            50,
            50,
            logWindow,
            NULL,
            hInstance,
            NULL
        );

        return logWindow;
    }
}