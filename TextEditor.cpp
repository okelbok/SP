#include "TextEditor.h"

#include "Resource.h"
#include "MainMenu.h"
#include "AboutDialogBox.h"

void RespondToPaintMessage(HWND hWnd)
{
    PAINTSTRUCT paintStruct;
    HDC hdc = BeginPaint(hWnd, &paintStruct);

    MessageBox(
        hWnd,
        L"WM_PAINT message has been received.",
        L"Message Capture Info",
        MB_OK | MB_ICONINFORMATION
    );

    EndPaint(hWnd, &paintStruct);
}

LRESULT CALLBACK TextEditorWindowProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (message)
    {
    case WM_PAINT:
        RespondToPaintMessage(hWnd);
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_CREATE:
        MessageBox(
            hWnd,
            L"WM_CREATE message has been received.",
            L"Message Capture Info",
            MB_OK | MB_ICONINFORMATION
        );

        break;

    case WM_DESTROY:
        MessageBox(
            hWnd,
            L"WM_DESTROY message has been received.",
            L"Message Capture Info",
            MB_OK | MB_ICONINFORMATION
        );

        PostQuitMessage(0);
        break;

    case WM_COMMAND:
        MessageBox(
            hWnd,
            L"WM_COMMAND message has been received.",
            L"Message Capture Info",
            MB_OK | MB_ICONINFORMATION
        );

        if (wParam == IDM_HELP_ABOUT)
        {
            DisplayAboutDialogBox(g_hInstance, hWnd);
            SetActiveWindow(hWnd);
        }

        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void RegisterTextEditorClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = TextEditorWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"TextEditorClass";
    wcex.hIconSm = wcex.hIcon;

    RegisterClassEx(&wcex);
    RegisterAboutDialogBoxClass(hInstance, wcex.hIcon);
}

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    g_hInstance = hInstance;

    HWND hWnd;
    HACCEL hAccel;
    HMENU hMenu;
    MSG msg;

    RegisterTextEditorClass(hInstance);

    hWnd = CreateWindowEx(
        0L,
        L"TextEditorClass",
        L"WinAPI Text Editor",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
    hMenu = CreateMainMenu();

    SetMenu(hWnd, hMenu);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, NULL, 0))
    {
        if (!TranslateAccelerator(hWnd, hAccel, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    DestroyAcceleratorTable(hAccel);
    DestroyMainMenu(hMenu);

    return (int)msg.wParam;
}
