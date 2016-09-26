#pragma once

#include <d3dx9.h>

class MATWORLD
{
	D3DXMATRIX matrix;
	D3DXMATRIX invMat;

	D3DXVECTOR3 translation;
	float scale;

	MATWORLD();
	MATWORLD(const MATWORLD&) = delete;
	MATWORLD& operator= (const MATWORLD&) = delete;

	void Set(const D3DXVECTOR3& translation, float scale) noexcept;

	const D3DXMATRIX* mat() const noexcept { return &matrix; }
	const D3DXMATRIX* inv() const noexcept { return &invMat; }

	const D3DXVECTOR3& Translation() const noexcept { return translation; }
	float Scale() const noexcept { return scale; }

	friend class GRAPHICS;
};
