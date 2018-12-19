#pragma once

struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};

class OBJLoader
{
private:
	vector<Vector3> Position;
	vector<Vector2> TexCoord;
	vector<Vector3> Normal;

	vector<VERTEX>  Vertex;
	vector<DWORD> Index;
	vector<DWORD> Attribute;

	vector <CacheEntry*> VertexCache;

	void CreateMesh(LPD3DXMESH * mesh);
	void MtlLoad(const string & mtlName);
	DWORD AddVertex(UINT hash, VERTEX* pVertex);
public:
	OBJLoader();
	~OBJLoader();

	void OBJLoad(LPD3DXMESH * mesh, const string & objPath, const string & mapPath = "None");
};

