#include <math.h>
#include "..\\customfvf.h"
#include "shapes.h"

const float PI = 3.141529f;

void SHAPES::InitDefaultShapes()
{
	try
	{
		tab.resize(STANDARD_SHAPES_AMOUNT);

		for (auto it = tab.begin(); it != tab.end(); it++)
			*it = 0;

		InitStSquare();
		InitStCircle();
		InitStCube();
		InitStSphere();
	}
	catch (...)
	{
		for (auto it = tab.begin(); it != tab.end(); it++)
			if (*it)
				(*it)->Release();

		throw;
	}
}

void SHAPES::InitStSquare()
{
	if (FAILED(device->CreateVertexBuffer(4*sizeof(CUSTOMFVF), 
										  D3DUSAGE_WRITEONLY,
										  CUSTOMFVF_TYPE,
										  D3DPOOL_DEFAULT,
										  &tab[ST_SQUARE],
										  0)))
		throw 0;

	CUSTOMFVF* v;
	tab[ST_SQUARE]->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = CUSTOMFVF(0.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[1] = CUSTOMFVF(0.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[2] = CUSTOMFVF(0.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f});
	v[3] = CUSTOMFVF(0.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f});

	tab[ST_SQUARE]->Unlock();
}

void SHAPES::InitStCircle()
{
	if (FAILED(device->CreateVertexBuffer(precision*sizeof(CUSTOMFVF), 
										  D3DUSAGE_WRITEONLY,
										  CUSTOMFVF_TYPE,
										  D3DPOOL_DEFAULT,
										  &tab[ST_CIRCLE],
										  0)))
		throw 0;

	float fprec = static_cast<float>(precision);

	CUSTOMFVF* v;
	tab[ST_CIRCLE]->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	for (unsigned i = 0; i < precision; i++)
		v[i] = CUSTOMFVF(0.0f,
						 cos(2*PI*static_cast<float>(i)/fprec), 
						 sin(2*PI*static_cast<float>(i)/fprec), 
						 { 1.0f, 0.0f, 0.0f});

	tab[ST_CIRCLE]->Unlock();
}

void SHAPES::InitStCube()
{
	if (FAILED(device->CreateVertexBuffer(24*sizeof(CUSTOMFVF), 
										  D3DUSAGE_WRITEONLY,
										  CUSTOMFVF_TYPE,
										  D3DPOOL_DEFAULT,
										  &tab[ST_CUBE],
										  0)))
		throw 0;

	CUSTOMFVF* v;
	tab[ST_CUBE]->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = CUSTOMFVF(1.0f,1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[1] = CUSTOMFVF(1.0f,-1.0f,1.0f,{1.0f, 0.0f, 0.0f});
	v[2] = CUSTOMFVF(1.0f,1.0f,-1.0f,{1.0f, 0.0f, 0.0f});
	v[3] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{1.0f, 0.0f, 0.0f});

	v[4] = CUSTOMFVF(-1.0f,1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[5] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});
	v[6] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{-1.0f, 0.0f, 0.0f});
	v[7] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{-1.0f, 0.0f, 0.0f});

	v[8] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[9] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 1.0f, 0.0f});
	v[10] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});
	v[11] = CUSTOMFVF( 1.0f,1.0f,-1.0f,{0.0f, 1.0f, 0.0f});

	v[12] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[13] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});
	v[14] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, -1.0f, 0.0f});
	v[15] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, -1.0f, 0.0f});

	v[16] = CUSTOMFVF(1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[17] = CUSTOMFVF(-1.0f,1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[18] = CUSTOMFVF(1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});
	v[19] = CUSTOMFVF(-1.0f,-1.0f,1.0f,{0.0f, 0.0f, 1.0f});

	v[20] = CUSTOMFVF(1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[21] = CUSTOMFVF(1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[22] = CUSTOMFVF(-1.0f,1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	v[23] = CUSTOMFVF(-1.0f,-1.0f,-1.0f,{0.0f, 0.0f, -1.0f});
	
	tab[ST_CUBE]->Unlock();
}

void SHAPES::InitStSphere()
{
	if (FAILED(device->CreateVertexBuffer((2*(precision+2)+2*(precision+1)*(precision-2))*sizeof(CUSTOMFVF), 
										  D3DUSAGE_WRITEONLY,
										  CUSTOMFVF_TYPE,
										  D3DPOOL_DEFAULT,
										  &tab[ST_SPHERE],
										  0)))
		throw 0;

	float fprec = static_cast<float>(precision);

	float x, y, z;

	CUSTOMFVF* v;
	tab[ST_SPHERE]->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	// górna czapeczka
	v[0] = CUSTOMFVF(0.0f, 0.0f, 1.0f, {0.0f, 0.0f, 1.0f});

	unsigned i = 1;
	for (unsigned j = 0; j <= precision; j++)
	{
		x = cos(PI/2-PI/fprec)*cos(2*PI*static_cast<float>(j)/fprec);
		y = cos(PI/2-PI/fprec)*sin(2*PI*static_cast<float>(j)/fprec);
		z = sin(PI/2-PI/fprec);

		v[i++] = CUSTOMFVF(x, y, z, {x, y, z});
	}

	// œrodek
	for (unsigned k = 1; k < precision-1; k++)
	{
		for (unsigned j = 0; j <= precision; j++)
		{
			x = cos(PI/2-PI*k/fprec)*cos(2*PI*static_cast<float>(j)/fprec);
			y = cos(PI/2-PI*k/fprec)*sin(2*PI*static_cast<float>(j)/fprec);
			z = sin(PI/2-PI*k/fprec);

			v[i++] = CUSTOMFVF(x, y, z, {x, y, z});

			x = cos(PI/2-PI*(k+1)/fprec)*cos(2*PI*static_cast<float>(j)/fprec);
			y = cos(PI/2-PI*(k+1)/fprec)*sin(2*PI*static_cast<float>(j)/fprec);
			z = sin(PI/2-PI*(k+1)/fprec);

			v[i++] = CUSTOMFVF(x, y, z, {x, y, z});
		}
	}

	// dolna czapeczka
	v[i++] = CUSTOMFVF(0.0, 0.0, -1.0f, {0.0f, 0.0f, -1.0f});

	for (unsigned j = 0; j <= precision; j++)
	{
		x = cos(PI/fprec-PI/2)*cos(-2*PI*static_cast<float>(j)/fprec);
		y = cos(PI/fprec-PI/2)*sin(-2*PI*static_cast<float>(j)/fprec);
		z = sin(PI/fprec-PI/2);

		v[i++] = CUSTOMFVF(x, y, z, {x, y, z});
	}

	tab[ST_SPHERE]->Unlock();
}

SHAPES::SHAPES(IDirect3DDevice9* dev, unsigned precision) : device(dev), precision(precision)
{
	InitDefaultShapes();
}

SHAPES::~SHAPES()
{
	for (auto it = tab.begin(); it != tab.end(); it++)
		if (*it)
			(*it)->Release();
}

void SHAPES::DrawShape(SHAPE_TYPE type) noexcept
{
	switch(type)
	{
	case ST_SQUARE:
		{
			device->SetStreamSource(0, tab[type], 0, sizeof(CUSTOMFVF));
			device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			break;
		}
	case ST_CIRCLE:
		{
			device->SetStreamSource(0, tab[type], 0, sizeof(CUSTOMFVF));
			device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, precision-1);
			break;
		}
	case ST_CUBE:
		{
			for (unsigned i = 0 ; i < 24; i += 4)
			{
				device->SetStreamSource(0, tab[type], i*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
				device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
			break;
		}
	case ST_SPHERE:
		{
			device->SetStreamSource(0, tab[type], 0, sizeof(CUSTOMFVF));
			device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, precision);

			for (unsigned k = 0; k < precision-2; k++)
			{
				device->SetStreamSource(0, tab[type], (precision+2+2*k*(precision+1))*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
				device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, precision*2);
			}

			device->SetStreamSource(0, tab[type], (precision+2+2*(precision-2)*(precision+1))*sizeof(CUSTOMFVF), sizeof(CUSTOMFVF));
			device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, precision);
			break;
		}
	}
}