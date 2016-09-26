#pragma once

#include <d3d9.h>

#define CUSTOMFVF_TYPE D3DFVF_XYZ | D3DFVF_NORMAL

struct CUSTOMFVF
{
	float x;
	float y;
	float z;
	D3DVECTOR normal;

	CUSTOMFVF(float in_x, float in_y, float in_z, D3DVECTOR in_normal) : 
		x(in_x),
		y(in_y),
		z(in_z),
		normal(in_normal) {}
};
