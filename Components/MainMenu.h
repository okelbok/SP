#pragma once
#include <windows.h>

#define IDM_FILE_OPEN     1001
#define IDM_FILE_SAVE     1002
#define IDM_FILE_EXIT     1003
#define IDM_EDIT_CUT      2001
#define IDM_EDIT_COPY     2002
#define IDM_EDIT_PASTE    2003
#define IDM_HELP_ABOUT    3001

HMENU CreateMainMenu();
void DestroyMainMenu(HMENU hMainMenu);
