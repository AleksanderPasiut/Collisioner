#include <math.h>
#include "..\\menu\\menu.h"
#include "scene.h"

void SCENE::InitWVP() noexcept
{ 
	graphics->SetWorld(D3DXVECTOR3(0, 0, 0), 1.0f);
	graphics->SetView(8.0f, 0, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	graphics->SetProjection(45, 0.01f, 100);
}
void SCENE::InitElements()
{
	try
	{
		switch(scene_properties.sm)
		{
		case SM_ATOM: shell = 0; break;
		case SM_SHELL: shell = new SHELL(graphics, scene_properties); break;
		}

		BALL::G = scene_properties.G;

		try
		{
			for (unsigned i = 0; i < scene_properties.amount; i++)
				balls.push_back(new BALL(graphics, balls, shell, scene_properties));
		}
		catch (int)
		{
			MessageBox(graphics->RetHwnd(), "Nie uda³o siê umieœciæ wszystkich kulek.", "B³¹d", MB_OK);
		}
	}
	catch(...)
	{
		DelElements();
		throw;
	}
}
void SCENE::CenterBalls() noexcept
{
	float mass = 0;
	D3DXVECTOR3 mass_center(0, 0, 0);
	for (auto it = balls.begin(); it != balls.end(); it++)
	{
		mass += (*it)->mass;
		mass_center += (*it)->mass * (*it)->position;
	}

	mass_center /= mass;

	for (auto it = balls.begin(); it != balls.end(); it++)
		(*it)->position -= mass_center;
}
void SCENE::DelElements() noexcept
{
	for (auto it = balls.begin(); it != balls.end(); it++)
		delete *it;

	delete shell;

	balls.clear();
	shell = 0;
}

SCENE::SCENE(GRAPHICS* graphics) : 
	graphics(graphics)
{
	InitWVP();
	InitElements();
}
SCENE::~SCENE() noexcept
{
	DelElements();
}

void SCENE::Render() noexcept
{
	graphics->BeginScene();
	
	for (auto it = balls.begin(); it != balls.end(); it++)
		(*it)->Render();

	if (shell)
		shell->Render();

	graphics->EndScene();
}
void SCENE::Action() noexcept
{
	if (scene_properties.sm == SM_ATOM)
	{
		if (scene_properties.center_balls)
			CenterBalls();

		for (auto it = balls.begin(); it != balls.end(); it++)
			(*it)->Gravity(balls);
	}

	for (auto it = balls.begin(); it != balls.end(); it++)
		(*it)->Collisions(balls, shell);

	for (auto it = balls.begin(); it != balls.end(); it++)
		(*it)->Move();

	if (!rotation.clicked)
		graphics->HorizontalCameraRotation(scene_properties.horizontal_rotation_speed);
}
void SCENE::Mouse(UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN: InitRotation(wParam, lParam); break;
	case WM_MOUSEMOVE: Rotate(wParam, lParam); break;
	case WM_LBUTTONUP: EndRotation(); break;
	case WM_MOUSEWHEEL: Zoom(wParam); break;
	}
}
void SCENE::Command(WPARAM wParam, LPARAM lParam) noexcept
{
	switch(LOWORD(wParam))
	{
		case CMM_SETTINGS:
		{
			SCENE_PROPERTIES new_scene_properties = scene_properties;

			if (DialogBoxParam(0, "dialog_settings",
							   graphics->RetHwnd(),
							   reinterpret_cast<DLGPROC>(DialogSettingsProc),
							   reinterpret_cast<LPARAM>(&new_scene_properties)))
			{
				scene_properties = new_scene_properties;
				DelElements();
				InitElements();
			}

			break;
		}
		case CMM_QUIT:
		{
			PostQuitMessage(0);
			break;
		}
	}
}