#include "DXUT.h"
#include "ModelViewer.h"


ModelViewer::ModelViewer()
{
}


ModelViewer::~ModelViewer()
{
	SAFE_DELETE(Model);
}

void ModelViewer::InitModel(const string & objPath, const string & mapPath)
{
	Model = new Mesh;

	loader.OBJLoad(Model, objPath, mapPath);

	vRot = Vector3(0.f, 0.f, 0.f);
	D3DXMatrixIdentity(&matWorld);
}

void ModelViewer::Update()
{
	float speed = 100.f;

	if (GetAsyncKeyState(VK_UP))
		vRot.x -= D3DXToRadian(100 * DXUTGetElapsedTime());
	if (GetAsyncKeyState(VK_DOWN))
		vRot.x += D3DXToRadian(100 * DXUTGetElapsedTime());
	if (GetAsyncKeyState(VK_LEFT))
		vRot.y += D3DXToRadian(100 * DXUTGetElapsedTime());
	if (GetAsyncKeyState(VK_RIGHT))
		vRot.y -= D3DXToRadian(100 * DXUTGetElapsedTime());
	if (GetAsyncKeyState('Q'))
		vRot.z -= D3DXToRadian(100 * DXUTGetElapsedTime());
	if (GetAsyncKeyState('E'))
		vRot.z += D3DXToRadian(100 * DXUTGetElapsedTime());
	if (GetAsyncKeyState('R'))
		vRot.x = vRot.y = vRot.z =0.f;

}

void ModelViewer::ModelRender()
{
	SetTransform();

	g_device->SetTransform(D3DTS_WORLD, &matWorld);

	for (int i = 0; i < Model->vMaterial.size(); ++i)
	{
		if (Model->vMaterial[i]->map)
			g_device->SetTexture(0, Model->vMaterial[i]->map->lpTex);
		else
			g_device->SetTexture(0, nullptr);

		g_device->SetMaterial(&Model->vMaterial[i]->material);
		Model->lpD3DXMesh->DrawSubset(i);
	}
}

void ModelViewer::SetTransform()
{
	D3DXMATRIX rX;
	D3DXMatrixRotationX(&rX, vRot.x);

	D3DXMATRIX rY;
	D3DXMatrixRotationY(&rY, vRot.y);

	D3DXMATRIX rZ;
	D3DXMatrixRotationZ(&rZ, vRot.z);

	matWorld = rX * rY * rZ;
}
