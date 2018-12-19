#pragma once


enum SYSTEM
{
	WINSIZEX = 1280,
	WINSIZEY = 720,
};

#define g_device DXUTGetD3D9Device()

#ifdef DEBUG
#define DEBUG_LOG(s) cout << s << endl
#else
#define DEBUG_LOG(s)
#endif

#include <iostream>	
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <map>

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix = D3DXMATRIX;

using namespace std;

#include "ImageManager.h"

struct Material
{
	string mtlName;

	D3DMATERIAL9 material;
	texture * map = nullptr;

	float fAlpha = 1;
	float fIllum;
	float fNs;
};

struct Mesh
{
	LPD3DXMESH lpD3DXMesh;
	vector<Material*> vMaterial;

	~Mesh()
	{
		for (auto Iter : vMaterial)
			SAFE_DELETE(Iter);
		
		vMaterial.clear();

		SAFE_RELEASE(lpD3DXMesh);
	}
};

struct VERTEX
{
	Vector3 pos;
	Vector3 normal;
	Vector2 tex;

	VERTEX(Vector3 _pos, Vector2 _tex, Vector3 _normal)
		:pos(_pos), tex(_tex), normal(_normal)
	{}
	VERTEX(){}
};
#define VERTEXFVF D3DFVF_XYZ | D3DFVF_NORMAL| D3DFVF_TEX1


