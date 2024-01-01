#pragma once

#include <windows.h>


#define Window HWND

namespace UI
{
    HWND creatButton(
        LPCWSTR buttonText,
        DWORD buttonStyles,
        int xPosition,
        int yPosition,
        int buttonWidth,
        int buttonHeight,
        HWND parentWindow,
        HMENU butonMenu,
        HINSTANCE& hInst,
        LPVOID lpParam);

    HWND logWindow(
        LPCWSTR lpWindowName,
        HWND hWndParent,
        HMENU hMenu,
        HINSTANCE hInstance,
        LPVOID lpParam);

}