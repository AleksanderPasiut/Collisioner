#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

enum SHAPE_TYPE
{
	ST_SQUARE = 0,
	ST_CIRCLE = 1,
	ST_CUBE = 2,
	ST_SPHERE = 3
};

class SHAPES
{
	static const unsigned STANDARD_SHAPES_AMOUNT = 4;
	std::vector<IDirect3DVertexBuffer9*> tab;

	IDirect3DDevice9* device;
	unsigned precision;

	void InitDefaultShapes();
	void InitStSquare();
	void InitStCircle();
	void InitStCube();
	void InitStSphere();

	SHAPES(IDirect3DDevice9*, unsigned precision = 50);
	SHAPES(const SHAPES&) = delete;
	SHAPES& operator= (const SHAPES&) = delete;
	~SHAPES() noexcept;

	void DrawShape(SHAPE_TYPE type) noexcept;

	friend class GRAPHICS;
};
