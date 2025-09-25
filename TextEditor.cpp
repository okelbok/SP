#include "TextEditor.h"

#include <ctime>

#include "Resources/resource.h"
#include "Components/MainMenu.h"
#include "Components/AboutDialogBox.h"
#include "Components/SpriteWindow.h"

HINSTANCE g_hInstance;
HWND g_hSpriteWnd = NULL;

LRESULT RespondToPaintMessage(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    PAINTSTRUCT paintStruct;
    HDC hdc = BeginPaint(hWnd, &paintStruct);
    LRESULT result;

    if (g_hSpriteWnd != NULL)
    {
        result = 0;
    }
    else
    {
        MessageBox(
            hWnd,
            L"WM_PAINT message has been received.",
            L"Message Capture Info",
            MB_OK | MB_ICONINFORMATION
        );

        result = DefWindowProc(hWnd, message, wParam, lParam);
    }

    EndPaint(hWnd, &paintStruct);

    return result;
}

void ResetInactivityTimer(HWND hWnd)
{
    KillTimer(hWnd, IDT_INACTIVITY_TIMER);

    if (g_hSpriteWnd != NULL)
    {
        DestroySpriteWindow(g_hSpriteWnd);
        g_hSpriteWnd = NULL;
    }

    SetTimer(hWnd, IDT_INACTIVITY_TIMER, INACTIVITY_TIMEOUT, NULL);
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
    case WM_CREATE:
        SetTimer(hWnd, IDT_INACTIVITY_TIMER, INACTIVITY_TIMEOUT, NULL);
        
        MessageBox(
            hWnd,
            L"WM_CREATE message has been received.",
            L"Message Capture Info",
            MB_OK | MB_ICONINFORMATION
        );

        break;

    case WM_NCPAINT:
        ResetInactivityTimer(hWnd);

        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_PAINT:
        return RespondToPaintMessage(hWnd, message, wParam, lParam);

    case WM_TIMER:
        if (wParam == IDT_INACTIVITY_TIMER)
        {
            if (g_hSpriteWnd == NULL)
            {
                g_hSpriteWnd = DisplaySpriteWindow(g_hInstance, hWnd);
            }
        }

        break;

    case WM_PARENTNOTIFY:
        switch (LOWORD(wParam))
        {
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            ResetInactivityTimer(hWnd);
        }

        break;

    case WM_MOUSEMOVE:
        if (g_hSpriteWnd == NULL)
        {
            break;
        }

    case WM_KEYDOWN:
        ResetInactivityTimer(hWnd);

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

    case WM_DESTROY:
        MessageBox(
            hWnd,
            L"WM_DESTROY message has been received.",
            L"Message Capture Info",
            MB_OK | MB_ICONINFORMATION
        );

        KillTimer(hWnd, IDT_INACTIVITY_TIMER);
        PostQuitMessage(0);

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
    RegisterSpriteWindowClass(hInstance);
}

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    srand(static_cast<unsigned int>(time(NULL)));

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
