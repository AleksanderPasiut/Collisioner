#pragma once

#include "..\\..\\graphics\\graphics.h"
#include "..\\scene_properties.h"

enum WALL_TYPE
{
	X_POS_IN = 0,
	X_NEG_IN = 1,
	Y_POS_IN = 2,
	Y_NEG_IN = 3,
	Z_POS_IN = 4,
	Z_NEG_IN = 5,

	X_POS_OUT = 6,
	X_NEG_OUT = 7,
	Y_POS_OUT = 8,
	Y_NEG_OUT = 9,
	Z_POS_OUT = 10,
	Z_NEG_OUT = 11,
};

class SHELL
{
	GRAPHICS* graphics;
	float fill_factor;
	float size;

	D3DXMATRIX wall[12];

	inline void InitMatrices() noexcept;

	SHELL(GRAPHICS*, const SCENE_PROPERTIES& sp);
	SHELL(const SHELL&) = delete;
	SHELL& operator= (const SHELL&) = delete;

	void Render() noexcept;

	friend class BALL;
	friend class SCENE;
};