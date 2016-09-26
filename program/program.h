#pragma once

#include <Windows.h>

#include "mainwindow\\mainwindow.h"
#include "graphics\\graphics.h"
#include "menu\\menu.h"
#include "scene\\scene.h"

class PROGRAM
{
	MAINWINDOW* mainWindow;
	GRAPHICS* graphics;
	MENU* menu;
	SCENE* scene;

	PROGRAM(HINSTANCE, WNDPROC);
	PROGRAM(const PROGRAM&) = delete;
	PROGRAM& operator= (const PROGRAM&) = delete;
	~PROGRAM() noexcept;

	LRESULT Message(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT Idle() noexcept;

	friend LRESULT CALLBACK EventProc(HWND, UINT, WPARAM, LPARAM);
	friend int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
};

