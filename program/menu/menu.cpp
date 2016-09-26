#include "menu.h"

MENU::MENU(HWND hwnd) : hwnd(hwnd)
{
	hMotherMenu = LoadMenu(0, "context_menu");
	hMenu = GetSubMenu(hMotherMenu, 0);
}
MENU::~MENU() noexcept
{
	DestroyMenu(hMenu);
	DestroyMenu(hMotherMenu);
}

void MENU::Mouse(WPARAM wParam, LPARAM lParam) noexcept
{
	TrackPopupMenu(hMenu, TPM_LEFTBUTTON, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0, hwnd, 0);
}