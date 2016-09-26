#include <cmath>

#include "matview.h"

MATVIEW::MATVIEW()
{
	D3DXMatrixIdentity(&matrix);
	D3DXMatrixIdentity(&invMat);
}

void MATVIEW::SetView(float radius, float phi, float theta,
					  const D3DXVECTOR3& argLookAtPoint,
					  const D3DXVECTOR3& argUpDirection) noexcept
{
	this->radius = radius;
	this->phi = phi;
	this->theta = theta;


	D3DXVECTOR3 camera_pos = { radius*cos(theta)*cos(phi),
							   radius*cos(theta)*sin(phi),
							   radius*sin(theta) };
	look_at_point = argLookAtPoint;
	up_direction = argUpDirection;

	D3DXMatrixLookAtLH(&matrix,	&camera_pos, &look_at_point, &up_direction);
	D3DXMatrixInverse(&invMat, 0, &matrix);
}