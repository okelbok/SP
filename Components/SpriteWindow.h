#pragma once
#include <windows.h>

#define IDT_SPRITE_TIMER 10002

#define SPRITE_TIMEOUT   8

void RegisterSpriteWindowClass(HINSTANCE hInstance);
HWND DisplaySpriteWindow(HINSTANCE hInstance, HWND hWnd);
void DestroySpriteWindow(HWND hSpriteWnd);