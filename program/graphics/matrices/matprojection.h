#pragma once

#include <d3dx9.h>

class MATPROJECTION
{
	D3DXMATRIX matrix;
	D3DXMATRIX invMat;
	float angle;
	float plane_near;
	float plane_far;

	MATPROJECTION();
	MATPROJECTION(const MATPROJECTION&) = delete;
	MATPROJECTION& operator= (const MATPROJECTION&) = delete;

	void SetProjection(HWND hwnd, float angle, float plane_near, float plane_far) noexcept;

	const D3DXMATRIX* mat() const noexcept { return &matrix; }
	const D3DXMATRIX* inv() const noexcept { return &invMat; }
	float fAngle() const noexcept { return angle; }
	float fPlaneNear() const noexcept { return plane_near; }
	float fPlaneFar() const noexcept { return plane_far; }

	friend class GRAPHICS;
};