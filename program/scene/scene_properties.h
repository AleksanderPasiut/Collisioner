#pragma once

#include <Windows.h>

enum SCENE_MODE
{
	SM_SHELL,
	SM_ATOM
};

class SCENE_PROPERTIES
{
	// modifiable ball properties
	unsigned amount;
	float radius_min;
	float radius_max;
	bool mass_radius_equivalent;
	float mass_min;
	float mass_max;
	float speed_min;
	float speed_max;
	
	// non-modifiable ball properties
	unsigned material_id_min;
	unsigned material_id_max;
	bool material_exclusiveness;

	// modifiable shell and ball properties depending on scene mode
	SCENE_MODE sm;
	float dist_from_center;
	float G;
	bool center_balls;
	float shell_size;
	float shell_fill_factor;

	// remaining settings
	float horizontal_rotation_speed;

	void LoadDefaultValues() noexcept;
	void LoadFromFile();
	void CheckCorrectness();
	void SaveToFile() const noexcept;

	SCENE_PROPERTIES();
	~SCENE_PROPERTIES() noexcept;

	friend class SHELL;
	friend class BALL;
	friend class SCENE;
	friend class DIALOG;
	friend BOOL CALLBACK DialogSettingsProc(HWND, UINT, WPARAM, LPARAM);
};
