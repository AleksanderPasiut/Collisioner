#include <fstream>

#include "scene_properties.h"
#include "..\\menu\\dialog\\dialog.h"

const char path[] = "config.cfg";

void SCENE_PROPERTIES::LoadDefaultValues() noexcept
{
	amount = 30;
	radius_min = 0.2f;
	radius_max = 0.25f;
	mass_radius_equivalent = true;
	mass_min = 1.0f;
	mass_max = 1.0f;
	speed_min = 0.0f;
	speed_max = 1.0f;

	material_id_min = 0;
	material_id_max = 5;
	material_exclusiveness = false;

	sm = SM_SHELL;
	dist_from_center = 6.0f;
	G = 0.5f;
	center_balls = true;
	shell_size = 2.0f;
	shell_fill_factor = 0.1f;

	horizontal_rotation_speed = 2.0f;
}
void SCENE_PROPERTIES::LoadFromFile()
{
	using namespace std;

	fstream FS(path, fstream::in);

	if (!FS)
		throw 0;

	FS.read(reinterpret_cast<char*>(this), sizeof(SCENE_PROPERTIES));

	FS.close();
}
void SCENE_PROPERTIES::CheckCorrectness()
{
	if (amount > DIALOG::max_amount ||
		radius_min < shell_fill_factor || radius_max < radius_min || DIALOG::max_radius < radius_max ||
		mass_min <= 0 || mass_max < mass_min || DIALOG::max_mass < mass_max ||
		speed_min < 0 || speed_max < speed_min || DIALOG::max_speed < speed_max ||
		dist_from_center < 0 || DIALOG::max_dist_from_center < dist_from_center ||
		G < 0 || DIALOG::max_G < G ||
		shell_size < 0 || DIALOG::max_shell_size < shell_size || shell_size <= radius_max ||
		shell_fill_factor < 0)
		throw 0;
}
void SCENE_PROPERTIES::SaveToFile() const noexcept
{
	using namespace std;

	fstream FS(path, fstream::out);

	if (!FS)
		return;

	FS.write(reinterpret_cast<const char*>(this), sizeof(SCENE_PROPERTIES));

	FS.close();
}

SCENE_PROPERTIES::SCENE_PROPERTIES()
{
	try
	{
		LoadFromFile();
		CheckCorrectness();
	}
	catch(...)
	{
		LoadDefaultValues();
	}
}
SCENE_PROPERTIES::~SCENE_PROPERTIES() noexcept
{
	SaveToFile();
}
