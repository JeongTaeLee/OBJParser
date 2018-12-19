#pragma once

struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};

class OBJLoader
{
private:
	string OBJPath;

	vector<Vector3> Position;
	vector<Vector2> TexCoord;
	vector<Vector3> Normal;

	vector<VERTEX>  Vertex;
	vector<DWORD> Index;
	vector<DWORD> Attribute;

	vector <CacheEntry*> VertexCache;

	string mtlPath;

	void CreateMesh(LPD3DXMESH * mesh);
	void MtlLoad(const string & mtlName, Mesh * mesh, const string & mapPath = "None");
	DWORD AddVertex(UINT hash, VERTEX* pVertex);
public:
	OBJLoader();
	~OBJLoader();

	void OBJLoad(Mesh * mesh, const string & objPath, const string & mapPath = "None");
};

