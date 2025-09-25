#include "SpriteWindow.h"

bool g_bSpriteWindowReady = false;

int g_spriteX = 100;
int g_spriteY = 100;

int g_spriteSize = 60;

int g_speedX = 12;
int g_speedY = 8;

COLORREF g_spriteColor = RGB(255, 0, 0);

HBRUSH CreateRandomBrush()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;

    g_spriteColor = RGB(r, g, b);

    return CreateSolidBrush(g_spriteColor);
}

LRESULT CALLBACK SpriteWindowProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (message)
    {
    case WM_CREATE:
        g_bSpriteWindowReady = false;

        SetTimer(hWnd, IDT_SPRITE_TIMER, SPRITE_TIMEOUT, NULL);

        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_MOUSEMOVE:
        if (g_bSpriteWindowReady)
        {
            SendMessage(GetParent(hWnd), WM_MOUSEMOVE, wParam, lParam);

            break;
        }
        else
        {
            g_bSpriteWindowReady = true;

            return DefWindowProc(hWnd, message, wParam, lParam);
        }

    case WM_PAINT:
    {
        PAINTSTRUCT paintStruct;
        HDC hdc = BeginPaint(hWnd, &paintStruct);

        HBRUSH hBrush = CreateSolidBrush(g_spriteColor);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        HPEN hPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
        HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

        Ellipse(hdc, g_spriteX, g_spriteY, g_spriteX + g_spriteSize, g_spriteY + g_spriteSize);

        SelectObject(hdc, hOldBrush);
        SelectObject(hdc, hOldPen);

        DeleteObject(hBrush);
        DeleteObject(hPen);

        SwapBuffers(hdc); // double buffering for smoother image

        EndPaint(hWnd, &paintStruct);

        break;
    }

    case WM_TIMER:
    {
        RECT clientRect;

        GetClientRect(hWnd, &clientRect);

        int clientWidth = clientRect.right - clientRect.left;
        int clientHeight = clientRect.bottom - clientRect.top;

        g_spriteX += g_speedX;
        g_spriteY += g_speedY;

        if (g_spriteX <= 0)
        {
            g_spriteX = 0;
            g_speedX = -g_speedX;

            DeleteObject(CreateRandomBrush());
        }
        else if (g_spriteX + g_spriteSize >= clientWidth)
        {
            g_spriteX = clientWidth - g_spriteSize;
            g_speedX = -g_speedX;

            DeleteObject(CreateRandomBrush());
        }

        if (g_spriteY <= 0)
        {
            g_spriteY = 0;
            g_speedY = -g_speedY;

            DeleteObject(CreateRandomBrush());
        }
        else if (g_spriteY + g_spriteSize >= clientHeight)
        {
            g_spriteY = clientHeight - g_spriteSize;
            g_speedY = -g_speedY;

            DeleteObject(CreateRandomBrush());
        }

        InvalidateRect(hWnd, NULL, TRUE);

        break;
    }

    case WM_DESTROY:
        KillTimer(hWnd, IDT_SPRITE_TIMER);

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

void RegisterSpriteWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcexSpriteWindow;

    wcexSpriteWindow.cbSize = sizeof(WNDCLASSEX);
    wcexSpriteWindow.style = CS_HREDRAW | CS_VREDRAW;
    wcexSpriteWindow.lpfnWndProc = SpriteWindowProc;
    wcexSpriteWindow.cbClsExtra = 0;
    wcexSpriteWindow.cbWndExtra = 0;
    wcexSpriteWindow.hInstance = hInstance;
    wcexSpriteWindow.hIcon = NULL;
    wcexSpriteWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcexSpriteWindow.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcexSpriteWindow.lpszMenuName = NULL;
    wcexSpriteWindow.lpszClassName = L"SpriteWindowClass";
    wcexSpriteWindow.hIconSm = NULL;

    RegisterClassEx(&wcexSpriteWindow);
}

HWND DisplaySpriteWindow(HINSTANCE hInstance, HWND hWnd)
{
    HWND hSpriteWnd;
    RECT clientRect;

    GetClientRect(hWnd, &clientRect);

    hSpriteWnd = CreateWindowEx(
        0,
        L"SpriteWindowClass",
        L"",
        WS_CHILD | WS_VISIBLE,
        0,
        0,
        clientRect.right,
        clientRect.bottom,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hSpriteWnd, SW_SHOW);
    UpdateWindow(hSpriteWnd);

    return hSpriteWnd;
}

void DestroySpriteWindow(HWND hSpriteWnd)
{
    DestroyWindow(hSpriteWnd);
}