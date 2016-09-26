#pragma once

#include "program.h"

PROGRAM::PROGRAM(HINSTANCE hInstance, WNDPROC wndproc)
{
	srand(GetTickCount());

	try
	{
		mainWindow = new MAINWINDOW(hInstance, wndproc);

		try
		{
			graphics = new GRAPHICS(mainWindow->RetHwnd());

			try
			{
				menu = new MENU(mainWindow->RetHwnd());

				try
				{
					scene = new SCENE(graphics);
				}
				catch(...) { delete menu; throw; }
			}
			catch(...) { delete graphics; throw; }
		}
		catch(...) { delete mainWindow; throw; }
	}
	catch(...) { throw; }

	ShowWindow(mainWindow->RetHwnd(), SW_SHOWNORMAL);
}

PROGRAM::~PROGRAM() noexcept
{
	delete scene;
	delete menu;
	delete graphics;
	delete mainWindow;
}

LRESULT PROGRAM::Message(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_MOUSEWHEEL: scene->Mouse(uMsg, wParam, lParam); break;
	case WM_RBUTTONDOWN: menu->Mouse(wParam, lParam); break;
	case WM_COMMAND: scene->Command(wParam, lParam); break;
	case WM_CLOSE: PostQuitMessage(0); break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT PROGRAM::Idle() noexcept
{
	scene->Action();
	scene->Render();
	return 0;
}