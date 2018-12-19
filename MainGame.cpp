#include "DXUT.h"
#include "MainGame.h"
#include "OBJLoader.h"
#include "Camera.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

void MainGame::Init()
{
	g_device->SetRenderState(D3DRS_LIGHTING, false);
	g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	OBJLoader loader;
	loader.OBJLoad(&mesh, "./media/cup.obj");

	camera = new Camera;
}

void MainGame::Release()
{
	SAFE_DELETE(camera);
	SAFE_RELEASE(mesh);
}

void MainGame::Update()
{
}

void MainGame::Render()
{
	camera->SetTransform();

	Matrix matPos;
	D3DXMatrixTranslation(&matPos, 0.f, 0.f, 0.f);
	g_device->SetTransform(D3DTS_WORLD, &matPos);

	g_device->SetTexture(0, nullptr);

	mesh->DrawSubset(0);
}
