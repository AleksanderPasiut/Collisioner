#pragma once

#include "..\\graphics\\graphics.h"

#include "scene_properties.h"
#include "ball\\ball.h"
#include "shell\\shell.h"

#include "scene_rotation.h"

class SCENE
{
	GRAPHICS* graphics;

	SCENE_PROPERTIES scene_properties;

	SHELL* shell;
	std::vector<BALL*> balls;

	void InitWVP() noexcept;
	void InitElements();
	void CenterBalls() noexcept;
	void DelElements() noexcept;

	ROTATION rotation;
	void InitRotation(WPARAM, LPARAM) noexcept;
	void Rotate(WPARAM, LPARAM) noexcept;
	void EndRotation() noexcept;
	void Zoom(WPARAM wParam) noexcept;

	SCENE(GRAPHICS* graphics);
	SCENE(const SCENE&) = delete;
	SCENE& operator= (const SCENE&) = delete;
	~SCENE() noexcept;

	void Render() noexcept;
	void Action() noexcept;
	void Mouse(UINT, WPARAM, LPARAM) noexcept;
	void Command(WPARAM, LPARAM) noexcept;

	friend class PROGRAM;
};