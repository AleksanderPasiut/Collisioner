#pragma once

#include <Windows.h>

#include "..\\..\\scene\\scene_properties.h"

#define CTRL_NUMB 0
#define CTRL_GB_1 0x101
#define CTRL_GB_2 0x102
#define CTRL_GB_3 0x103
#define CTRL_GB_4 0x104
#define CTRL_GB_5 0x105
#define CTRL_EDIT_1 0x201
#define CTRL_EDIT_2 0x202
#define CTRL_EDIT_3 0x203
#define CTRL_EDIT_4 0x204
#define CTRL_EDIT_5 0x205
#define CTRL_EDIT_6 0x206
#define CTRL_EDIT_7 0x207
#define CTRL_EDIT_8 0x208
#define CTRL_EDIT_9 0x209
#define CTRL_EDIT_A 0x20a
#define CTRL_EDIT_B 0x20b
#define CTRL_EDIT_C 0x20c
#define CTRL_OK 0x301
#define CTRL_CANCEL 0x302
#define CTRL_ST_ATOM 0x401
#define CTRL_ST_SHELL 0x402
#define CTRL_CB_1 0x501
#define CTRL_CB_2 0x502

class DIALOG
{
	static const unsigned max_amount;
	static const float max_radius;
	static const float max_mass;
	static const float max_speed;
	static const float max_dist_from_center;
	static const float max_G;
	static const float max_shell_size;
	static const float max_shell_fill_factor;
	static const float max_horizontal_rotation_speed;

	static bool UnsignedLimiter(char buffer[5]) noexcept;
	static bool FloatLimiter(char buffer[5]) noexcept;

	static void MassMode(HWND, const SCENE_PROPERTIES*) noexcept;
	static void AnimMode(HWND, const SCENE_PROPERTIES*) noexcept;
	static void InitiateSettingsControlStates(HWND, const SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit1(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit2(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit3(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit4(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit5(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit6(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit7(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit8(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEdit9(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEditA(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEditB(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;
	static void CtrlEditC(HWND, WPARAM, SCENE_PROPERTIES*) noexcept;

	friend class SCENE_PROPERTIES;
	friend BOOL CALLBACK DialogSettingsProc(HWND, UINT, WPARAM, LPARAM);
};

BOOL CALLBACK DialogSettingsProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
