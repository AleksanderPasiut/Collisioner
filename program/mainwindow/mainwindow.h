#pragma once

#include <Windows.h>

class MAINWINDOW
{
	WNDCLASSEX wc;
	HWND hwnd;

	inline void InitWindowClass(HINSTANCE, WNDPROC);
	inline void InitHwnd();

	MAINWINDOW(HINSTANCE, WNDPROC);
	MAINWINDOW(const MAINWINDOW&) = delete;
	MAINWINDOW& operator= (const MAINWINDOW&) = delete;
	~MAINWINDOW() noexcept;

	HWND RetHwnd() const noexcept { return hwnd; }

	friend class PROGRAM;
};