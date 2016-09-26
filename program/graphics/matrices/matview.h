#pragma once

#include <d3dx9.h>

class MATVIEW
{
	D3DXMATRIX matrix;
	D3DXMATRIX invMat;
	float radius;
	float phi;
	float theta;
	D3DXVECTOR3 look_at_point;
	D3DXVECTOR3 up_direction;

	MATVIEW();
	MATVIEW(const MATVIEW&) = delete;
	MATVIEW& operator= (const MATVIEW&) = delete;

	void SetView(float radius, float phi, float theta,
				 const D3DXVECTOR3& look_at_point,
				 const D3DXVECTOR3& up_direction) noexcept;

	const D3DXMATRIX* mat() const noexcept { return &matrix; }
	const D3DXMATRIX* inv() const noexcept { return &invMat; }
	float Radius() const noexcept { return radius; }
	float Phi() const noexcept { return phi; }
	float Theta() const noexcept { return theta; }
	const D3DXVECTOR3& vecLookAtPoint() const noexcept { return look_at_point; }
	const D3DXVECTOR3& vecUpDirection() const noexcept { return up_direction; }

	friend class GRAPHICS;
};
