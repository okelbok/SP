#pragma once
#include <windows.h>

HINSTANCE g_hInstance;

void RegisterTextEditorClass(HINSTANCE hInstance);
LRESULT CALLBACK TextEditorWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
