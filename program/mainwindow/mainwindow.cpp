#include "mainwindow.h"

void MAINWINDOW::InitWindowClass(HINSTANCE hInstance, WNDPROC wndproc)
{
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpfnWndProc = wndproc;
	wc.lpszClassName = "CollisionerAppWindowClass";
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

	if (!RegisterClassEx(&wc))
		throw 0;
}

void MAINWINDOW::InitHwnd()
{
	hwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		"Collisioner",
		WS_POPUP,
		0, //CW_USEDEFAULT,
		0, //CW_USEDEFAULT,
		GetSystemMetrics(SM_CXSCREEN), //CW_USEDEFAULT,
		GetSystemMetrics(SM_CYSCREEN), //CW_USEDEFAULT,
		0,
		0,
		wc.hInstance,
		0);

	if (!hwnd)
		throw 0;
}

MAINWINDOW::MAINWINDOW(HINSTANCE hInstance, WNDPROC wndproc)
{
	try
	{
		InitWindowClass(hInstance, wndproc);

		try
		{
			InitHwnd();
		}
		catch(...) { UnregisterClass(wc.lpszClassName, wc.hInstance); throw; }
	}
	catch(...) { throw; }
}

MAINWINDOW::~MAINWINDOW() noexcept
{
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}