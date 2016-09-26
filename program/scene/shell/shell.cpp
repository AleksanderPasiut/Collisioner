#include "shell.h"

const float PI = 3.141529f;

void SHELL::InitMatrices() noexcept
{
	#define PrepareMatrix(arg) D3DXMatrixMultiply(&wall[arg],D3DXMatrixMultiply(&tmp,&scaling,&rotation),&translation);

	D3DXMATRIX scaling, rotation, translation, tmp;
	D3DXMatrixScaling(&scaling, size-fill_factor, size-fill_factor, size-fill_factor);

	D3DXMatrixIdentity(&rotation);

	D3DXMatrixTranslation(&translation, size, 0, 0);
	PrepareMatrix(X_POS_OUT);
	D3DXMatrixTranslation(&translation, -size, 0, 0);
	PrepareMatrix(X_NEG_IN);
	D3DXMatrixRotationY(&rotation, PI);
	PrepareMatrix(X_NEG_OUT);
	D3DXMatrixTranslation(&translation, size, 0, 0);
	PrepareMatrix(X_POS_IN);

	D3DXMatrixRotationZ(&rotation, PI/2);

	D3DXMatrixTranslation(&translation, 0, size, 0);
	PrepareMatrix(Y_POS_OUT);
	D3DXMatrixTranslation(&translation, 0, -size, 0);
	PrepareMatrix(Y_NEG_IN);
	D3DXMatrixRotationZ(&rotation, -PI/2);
	PrepareMatrix(Y_NEG_OUT);
	D3DXMatrixTranslation(&translation, 0, size, 0);
	PrepareMatrix(Y_POS_IN);

	D3DXMatrixRotationY(&rotation, -PI/2);

	D3DXMatrixTranslation(&translation, 0, 0, size);
	PrepareMatrix(Z_POS_OUT);
	D3DXMatrixTranslation(&translation, 0, 0, -size);
	PrepareMatrix(Z_NEG_IN);
	D3DXMatrixRotationY(&rotation, PI/2);
	PrepareMatrix(Z_NEG_OUT);
	D3DXMatrixTranslation(&translation, 0, 0, size);
	PrepareMatrix(Z_POS_IN);
}

SHELL::SHELL(GRAPHICS* graphics, const SCENE_PROPERTIES& sp) : graphics(graphics), fill_factor(sp.shell_fill_factor), size(sp.shell_size)
{
	InitMatrices();
}

void SHELL::Render() noexcept
{
	graphics->SetMaterial(graphics->RetMaterial(MT_WALL));
	for (unsigned i = 0; i < 12; i++)
	{
		graphics->SetWorld(&wall[i]);
		graphics->DrawShape(ST_SQUARE);
	}
}