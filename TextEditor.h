#pragma once
#include <windows.h>

#define IDT_INACTIVITY_TIMER 10001

#define INACTIVITY_TIMEOUT   30000

void RegisterTextEditorClass(HINSTANCE hInstance);
LRESULT CALLBACK TextEditorWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
