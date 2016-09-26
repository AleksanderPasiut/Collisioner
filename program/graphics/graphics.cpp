#include "graphics.h"

void GRAPHICS::CreateDirect3DDevice()
{
	// anti-aliasing
	DWORD quality = 0;
	d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		D3DFMT_X8R8G8B8,
		true,
		D3DMULTISAMPLE_8_SAMPLES,
		&quality);
	
	// main structure
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = quality - 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	RECT rect;
	GetClientRect(hwnd, &rect);
	d3dpp.BackBufferWidth = rect.right-rect.left;
	d3dpp.BackBufferHeight = rect.bottom-rect.top;

	// device creation
	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev)))
		throw 0;

	// setting additional render states
	if (FAILED(d3ddev->SetRenderState(D3DRS_ZENABLE, true)))							throw 0;
	if (FAILED(d3ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true)))				throw 0;
	if (FAILED(d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true)))					throw 0;
	//if (FAILED(d3ddev->SetRenderState(D3DRS_SPECULARENABLE, true)))						throw 0;
	//if (FAILED(d3ddev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL)))	throw 0;
	if (FAILED(d3ddev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL)))	throw 0;
 	if (FAILED(d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD)))					throw 0;
 	if (FAILED(d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA)))				throw 0;
 	if (FAILED(d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA)))			throw 0;

	InitLights();
}
void GRAPHICS::InitLights()
{
	d3ddev->SetRenderState(D3DRS_AMBIENT, 0x00ffffff);
	d3ddev->SetRenderState(D3DRS_LIGHTING, true);

	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	light.Direction = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);

	d3ddev->SetLight(0, &light);
	d3ddev->LightEnable(0, true);
}

GRAPHICS::GRAPHICS(HWND hwnd) : 
	hwnd(hwnd),
	colorBack(D3DCOLOR_XRGB(0, 0, 0))
{
	try
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d)
			throw 0;

		try
		{
			CreateDirect3DDevice();

			try
			{
				shapes = new SHAPES(d3ddev);
			}
			catch(...) { d3ddev->Release(); throw; }
		}
		catch(...) { d3d->Release(); throw; }
	}
	catch(...) { throw; }
}

GRAPHICS::~GRAPHICS() noexcept
{
	delete shapes;
	d3ddev->Release();
	d3d->Release();
}

void GRAPHICS::BeginScene() noexcept
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, colorBack, 1.0f, 0);
	d3ddev->Clear(0, 0, D3DCLEAR_ZBUFFER, colorBack, 1.0f, 0);

	d3ddev->BeginScene();

	d3ddev->SetTransform(D3DTS_WORLD, matWorld.mat());
	d3ddev->SetTransform(D3DTS_VIEW, matView.mat());
	d3ddev->SetTransform(D3DTS_PROJECTION, matProjection.mat());

	d3ddev->SetFVF(CUSTOMFVF_TYPE);
}
void GRAPHICS::EndScene() noexcept
{
	d3ddev->EndScene();
	d3ddev->Present(0, 0, 0, 0);
}
