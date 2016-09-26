#include <Windows.h>

#include "program\\program.h"

PROGRAM* Program = 0;

LRESULT CALLBACK EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (Program)
		return Program->Message(hwnd, uMsg, wParam, lParam);
	else return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	try
	{
		Program = new PROGRAM(hInstance, EventProc);
	}
	catch(...) { return 0; }

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Program->Idle();
	}

	delete Program;
	return static_cast<int>(msg.wParam);
}