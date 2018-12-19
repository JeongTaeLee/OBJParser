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
	//g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	
	mesh = new Mesh;

	OBJLoader loader;
	loader.OBJLoad(mesh, "./media/cup.obj");
	
	camera = new Camera;
}

void MainGame::Release()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(mesh);

	ImageManager::ReleaseInst();
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

	for (int i = 0; i < mesh->vMaterial.size(); ++i)
	{
		if(mesh->vMaterial[i]->map)
			g_device->SetTexture(0, mesh->vMaterial[i]->map->lpTex);
		else
			g_device->SetTexture(0, nullptr);

		g_device->SetMaterial(&mesh->vMaterial[i]->material);
		mesh->lpD3DXMesh->DrawSubset(i);
	}
	
}
