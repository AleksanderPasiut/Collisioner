#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

enum MATERIAL_TYPE
{
	MT_RED = 0,
	MT_YELLOW = 1,
	MT_GREEN = 2,
	MT_BLUE = 3,
	MT_PURPLE = 4,
	MT_WHITE = 5,
	MT_WALL = 6
};

class MATERIALS
{
	static const unsigned STANDARD_MATERIALS_AMOUNT = 7;
	std::vector<D3DMATERIAL9*> tab;

	void InitDefaultMaterials();

	MATERIALS();
	MATERIALS(const MATERIALS&) = delete;
	MATERIALS& operator= (const MATERIALS&) = delete;
	~MATERIALS() noexcept;

	const D3DMATERIAL9* Ret(MATERIAL_TYPE type) const noexcept { return tab[type]; }

	friend class GRAPHICS;
};