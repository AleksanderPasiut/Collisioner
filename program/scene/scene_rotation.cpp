#include <windowsx.h>

#include "scene.h"

ROTATION::ROTATION() :
	clicked(false),
	speed(0.005f),
	init_phi(0.0f),
	init_theta(0.0f),
	click({0, 0}),
	theta_limit(1.5f),
	zoom_limit_in(4.0f),
	zoom_limit_out(40.0f),
	zoom_speed(1.1f)
{}

void SCENE::InitRotation(WPARAM wParam, LPARAM lParam) noexcept
{
	rotation.click.x = GET_X_LPARAM(lParam);
	rotation.click.y = GET_Y_LPARAM(lParam);
	rotation.init_phi = graphics->RetPhi();
	rotation.init_theta = graphics->RetTheta();
	rotation.clicked = true;
}

void SCENE::Rotate(WPARAM wParam, LPARAM lParam) noexcept
{
	if (!rotation.clicked)
		return;

	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	float phi = rotation.init_phi + rotation.speed*(pt.x-rotation.click.x);
	float theta = rotation.init_theta + rotation.speed*(pt.y-rotation.click.y);

	if (theta > rotation.theta_limit)
		theta = rotation.theta_limit;

	if (theta < -rotation.theta_limit)
		theta = -rotation.theta_limit;

	graphics->SetView(graphics->RetRadius(), phi, theta, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
}

void SCENE::EndRotation() noexcept
{
	rotation.clicked = false;
}

void SCENE::Zoom(WPARAM wParam) noexcept
{
	short delta = GET_WHEEL_DELTA_WPARAM(wParam);

	if (delta > 0 && graphics->RetRadius() > rotation.zoom_limit_in*rotation.zoom_speed)
		graphics->SetView(graphics->RetRadius()/rotation.zoom_speed,
						  graphics->RetPhi(),
						  graphics->RetTheta(),
						  graphics->RetLookAtPoint(),
						  graphics->RetUpDirection());
	else if (delta < 0 && graphics->RetRadius() < rotation.zoom_limit_out/rotation.zoom_speed)
		graphics->SetView(graphics->RetRadius()*rotation.zoom_speed,
						  graphics->RetPhi(),
						  graphics->RetTheta(),
						  graphics->RetLookAtPoint(),
						  graphics->RetUpDirection());
}