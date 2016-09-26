#include "materials.h"

void MATERIALS::InitDefaultMaterials()
{
	try
	{
		tab.resize(STANDARD_MATERIALS_AMOUNT);
		
		for (auto it = tab.begin(); it != tab.end(); it++)
			*it = 0;

		for (auto it = tab.begin(); it != tab.end(); it++)
		{
			*it = new D3DMATERIAL9;
			ZeroMemory(*it, sizeof(D3DMATERIAL9));
		}

		tab[MT_RED]->Diffuse	= D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		tab[MT_RED]->Ambient	= D3DXCOLOR(0.2f, 0.0f, 0.0f, 1.0f);

		tab[MT_YELLOW]->Diffuse = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		tab[MT_YELLOW]->Ambient = D3DXCOLOR(0.2f, 0.2f, 0.0f, 1.0f);

		tab[MT_GREEN]->Diffuse  = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		tab[MT_GREEN]->Ambient  = D3DXCOLOR(0.0f, 0.2f, 0.0f, 1.0f);

		tab[MT_BLUE]->Diffuse	= D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		tab[MT_BLUE]->Ambient	= D3DXCOLOR(0.0f, 0.0f, 0.2f, 1.0f);

		tab[MT_PURPLE]->Diffuse = D3DXCOLOR(0.7f, 0.0f, 1.0f, 1.0f);
		tab[MT_PURPLE]->Ambient = D3DXCOLOR(0.14f, 0.0f, 0.2f, 1.0f);

		tab[MT_WHITE]->Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		tab[MT_WHITE]->Ambient  = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		
		tab[MT_WALL]->Emissive = tab[MT_WALL]->Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.2f);
	}
	catch(...)
	{
		for (auto it = tab.begin(); it != tab.end(); it++)
			delete *it;

		throw;
	}
}

MATERIALS::MATERIALS()
{
	InitDefaultMaterials();
}

MATERIALS::~MATERIALS()
{
	for (auto it = tab.begin(); it != tab.end(); it++)
		delete *it;
}