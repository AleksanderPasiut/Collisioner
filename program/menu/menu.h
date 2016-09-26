#pragma once

#include <windows.h>
#include <windowsx.h>

#include "dialog\\dialog.h"

#define CMM_SETTINGS 0
#define CMM_QUIT 1

class MENU
{
	HWND hwnd;

	HMENU hMotherMenu;
	HMENU hMenu;

	MENU(HWND hwnd);
	MENU(const MENU&) = delete;
	MENU& operator= (const MENU&) = delete;
	~MENU() noexcept;

	void Mouse(WPARAM, LPARAM) noexcept;

	friend class PROGRAM;
};