#pragma once

#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#include "customfvf.h"

#include "matrices\\matworld.h"
#include "matrices\\matview.h"
#include "matrices\\matprojection.h"

#include "materials\\materials.h"
#include "shapes\\shapes.h"

class GRAPHICS
{
private:
	HWND hwnd;
	IDirect3D9* d3d;
	IDirect3DDevice9* d3ddev;
	D3DPRESENT_PARAMETERS d3dpp;

	MATWORLD matWorld;
	MATVIEW matView;
	MATPROJECTION matProjection;

	MATERIALS materials;
	SHAPES* shapes;

	D3DCOLOR colorBack;

private:
	inline void CreateDirect3DDevice();
	inline void InitLights();

public:
	GRAPHICS(HWND);
	GRAPHICS(const GRAPHICS&) = delete;
	GRAPHICS& operator= (const GRAPHICS&) = delete;
	~GRAPHICS() noexcept;

	void BeginScene() noexcept;
	void EndScene() noexcept;

public:	
	void SetColorBack(D3DCOLOR color) noexcept;
	void SetMaterial(const D3DMATERIAL9*) noexcept;
	void SetWorld(const D3DXVECTOR3& translation, float scale) noexcept;
	void SetWorld(const D3DXMATRIX* matrix) noexcept;
	void SetView(float radius, float phi, float theta, const D3DXVECTOR3& look_at_point, const D3DXVECTOR3& up_direction) noexcept;
	void SetProjection(float angle, float plane_near, float plane_far) noexcept;
	void HorizontalCameraRotation(float speed) noexcept;
	
	IDirect3DDevice9* Dev() noexcept { return d3ddev; }
	HWND RetHwnd() const noexcept { return hwnd; }
	const D3DCOLOR& RetColorBack() const noexcept { return colorBack; }
	const D3DMATERIAL9* RetMaterial(MATERIAL_TYPE type) const noexcept { return materials.Ret(type); }
	float RetRadius() const noexcept { return matView.Radius(); }
	float RetPhi() const noexcept { return matView.Phi(); }
	float RetTheta() const noexcept { return matView.Theta(); }
	const D3DXVECTOR3& RetLookAtPoint() const noexcept { return matView.vecLookAtPoint(); }
	const D3DXVECTOR3& RetUpDirection() const noexcept { return matView.vecUpDirection(); }
	float RetTimerInterval() const noexcept { return static_cast<float>(1/30.0f); }

	void DrawShape(SHAPE_TYPE type) noexcept { shapes->DrawShape(type); }
};