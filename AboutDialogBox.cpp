#include "AboutDialogBox.h"

LRESULT CALLBACK AboutDialogBoxProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (message)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            DestroyWindow(hWnd);
        }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    
    return 0;
}

void RegisterAboutDialogBoxClass(HINSTANCE hInstance, HICON hIcon)
{
    WNDCLASSEX wcexAboutDialogBox;

    wcexAboutDialogBox.cbSize = sizeof(WNDCLASSEX);
    wcexAboutDialogBox.style = CS_HREDRAW | CS_VREDRAW;
    wcexAboutDialogBox.lpfnWndProc = AboutDialogBoxProc;
    wcexAboutDialogBox.cbClsExtra = 0;
    wcexAboutDialogBox.cbWndExtra = 0;
    wcexAboutDialogBox.hInstance = hInstance;
    wcexAboutDialogBox.hIcon = hIcon;
    wcexAboutDialogBox.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcexAboutDialogBox.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcexAboutDialogBox.lpszMenuName = NULL;
    wcexAboutDialogBox.lpszClassName = L"AboutDialogBoxClass";
    wcexAboutDialogBox.hIconSm = hIcon;

    RegisterClassEx(&wcexAboutDialogBox);
}

void AddAboutInfo(HINSTANCE hInstance, HWND hWnd)
{
    HWND hStatic = CreateWindow(
        L"STATIC",
        L"This program is a simple text editor created using Windows API and C++.\nAuthor: Kolbeko Vlada, gr. 351003.",
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        10, 10, 260, 60,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    HWND hButton = CreateWindow(
        L"BUTTON",
        L"OK",
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
        110, 80, 80, 25,
        hWnd,
        (HMENU)IDOK,
        hInstance,
        NULL
    );
}

void DisplayAboutDialogBox(HINSTANCE hInstance, HWND hWnd)
{
    HWND hAboutDialogBoxWnd;
    MSG msg;

    hAboutDialogBoxWnd = CreateWindowEx(
        0L,
        L"AboutDialogBoxClass",
        L"About Program",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        300,
        150,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    SetWindowLong(hAboutDialogBoxWnd, GWL_STYLE,
        GetWindowLong(hAboutDialogBoxWnd, GWL_STYLE) & ~WS_MINIMIZEBOX);
    SetWindowLong(hAboutDialogBoxWnd, GWL_STYLE,
        GetWindowLong(hAboutDialogBoxWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);

    ShowWindow(hAboutDialogBoxWnd, SW_SHOWNORMAL);
    UpdateWindow(hAboutDialogBoxWnd);
    EnableWindow(hWnd, false);

    AddAboutInfo(hInstance, hAboutDialogBoxWnd);

    while (GetMessage(&msg, NULL, NULL, 0))
    {
        DispatchMessage(&msg);
    }

    EnableWindow(hWnd, true);
}