#include "matprojection.h"

MATPROJECTION::MATPROJECTION()
{
	D3DXMatrixIdentity(&matrix);
	D3DXMatrixIdentity(&invMat);
}

void MATPROJECTION::SetProjection(HWND hwnd,
								  float argAngle,
								  float argPlaneNear,
								  float argPlaneFar) noexcept
{
	angle = argAngle;
	plane_near = argPlaneNear;
	plane_far = argPlaneFar;

	RECT rect;
	GetClientRect(hwnd, &rect);

	D3DXMatrixPerspectiveFovLH(&matrix,
		D3DXToRadian(angle),
		static_cast<float>(rect.right-rect.left)/static_cast<float>(rect.bottom-rect.top),
		plane_near,
		plane_far);
}