#include "graphics.h"

void GRAPHICS::SetColorBack(D3DCOLOR color) noexcept
{
	colorBack = color;
}
void GRAPHICS::SetMaterial(const D3DMATERIAL9* material) noexcept
{
	d3ddev->SetMaterial(material);
}
void GRAPHICS::SetWorld(const D3DXVECTOR3& translation, float scale) noexcept
{
	matWorld.Set(translation, scale);
	d3ddev->SetTransform(D3DTS_WORLD, matWorld.mat());
}
void GRAPHICS::SetWorld(const D3DXMATRIX* matrix) noexcept
{
	d3ddev->SetTransform(D3DTS_WORLD, matrix);
}
void GRAPHICS::SetView(float radius, float phi, float theta, const D3DXVECTOR3& look_at_point, const D3DXVECTOR3& up_direction) noexcept
{
	matView.SetView(radius, phi, theta, look_at_point, up_direction);
	d3ddev->SetTransform(D3DTS_VIEW, matView.mat());
}
void GRAPHICS::SetProjection(float angle, float plane_near, float plane_far) noexcept
{
	matProjection.SetProjection(hwnd, angle, plane_near, plane_far);
	d3ddev->SetTransform(D3DTS_PROJECTION, matProjection.mat());
}
void GRAPHICS::HorizontalCameraRotation(float speed) noexcept
{
	matView.SetView(matView.Radius(), matView.Phi()+speed/1000, matView.Theta(), matView.vecLookAtPoint(), matView.vecUpDirection());
	d3ddev->SetTransform(D3DTS_VIEW, matView.mat());
}
