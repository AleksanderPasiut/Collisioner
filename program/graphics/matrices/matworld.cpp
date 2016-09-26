#include "matworld.h"

MATWORLD::MATWORLD()
{
	D3DXMatrixIdentity(&matrix);
	D3DXMatrixIdentity(&invMat);

	translation = D3DXVECTOR3(0, 0, 0);
	scale = 1;
}

void MATWORLD::Set(const D3DXVECTOR3& translation, float scale) noexcept
{
	D3DXMATRIX m1, m2;
	D3DXMatrixScaling(&m1, scale, scale, scale);
	D3DXMatrixTranslation(&m2, translation.x, translation.y, translation.z);
	D3DXMatrixMultiply(&matrix, &m1, &m2);

	D3DXMatrixInverse(&invMat, 0, &matrix);
}