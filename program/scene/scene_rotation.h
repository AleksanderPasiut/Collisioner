#pragma once

class ROTATION
{
	bool clicked;
	float speed;
	float init_phi;
	float init_theta;
	POINT click;

	float theta_limit;

	float zoom_limit_in;
	float zoom_limit_out;

	float zoom_speed;

	ROTATION();

	friend class SCENE;
};
