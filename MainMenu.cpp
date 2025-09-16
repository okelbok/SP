#include "MainMenu.h"

HMENU CreateMainMenu()
{
    HMENU hMainMenu = CreateMenu();
    HMENU hFileMenu = CreatePopupMenu();
    HMENU hEditMenu = CreatePopupMenu();
    HMENU hHelpMenu = CreatePopupMenu();

    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hFileMenu, L"File");
    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hEditMenu, L"Edit");
    AppendMenu(hMainMenu, MF_STRING | MF_POPUP, (UINT_PTR)hHelpMenu, L"Help");

    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, L"Open");
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, L"Save");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0L, NULL);
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, L"Exit");

    AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, L"Cut");
    AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, L"Copy");
    AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, L"Paste");

    AppendMenu(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, L"About Program");

    return hMainMenu;
}

void DestroyMainMenu(HMENU hMainMenu)
{
    HMENU hFileMenu = GetSubMenu(hMainMenu, 0);
    HMENU hEditMenu = GetSubMenu(hMainMenu, 1);
    HMENU hHelpMenu = GetSubMenu(hMainMenu, 2);

    DestroyMenu(hFileMenu);
    DestroyMenu(hEditMenu);
    DestroyMenu(hHelpMenu);

    DestroyMenu(hMainMenu);
}