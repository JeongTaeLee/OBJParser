#include "DXUT.h"
#include "MainGame.h"
#include "OBJLoader.h"
#include "Camera.h"
#include "ModelViewer.h"

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

	camera = new Camera;

	viewer = new ModelViewer;
	viewer->InitModel("./media/cup.obj");
}

void MainGame::Release()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(viewer);

	ImageManager::ReleaseInst();
}

void MainGame::Update()
{
	viewer->Update();
}

void MainGame::Render()
{
	camera->SetTransform();

	viewer->ModelRender();
}
