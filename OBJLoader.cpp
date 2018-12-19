#include "DXUT.h"
#include "OBJLoader.h"


OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}


void OBJLoader::CreateMesh(LPD3DXMESH * mesh)
{
	if (FAILED(D3DXCreateMeshFVF(Index.size() / 3, Vertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEXFVF, g_device, mesh)))
	{
		DEBUG_LOG("Failed D3DXCreateMeshFVF");
		return ;
	}

	VERTEX * vertices = nullptr;
	if (FAILED((*mesh)->LockVertexBuffer(0, (void**)&vertices)))
	{
		DEBUG_LOG("Failed LockVertexBuffer");
		return ;
	}

	memcpy(vertices, &Vertex[0], sizeof(VERTEX) * Vertex.size());
	(*mesh)->UnlockVertexBuffer();
	Vertex.clear();

	DWORD * indices = nullptr;
	if (FAILED((*mesh)->LockIndexBuffer(0, (void**)&indices)))
	{
		DEBUG_LOG("Failed LockIndexBuffer");
		return ;
	}

	memcpy(indices, &Index[0], sizeof(DWORD) * Index.size());
	(*mesh)->UnlockIndexBuffer();
	Index.clear();
	
	DWORD * attribute = nullptr;
	if (FAILED((*mesh)->LockAttributeBuffer(0, &attribute)))
	{
		DEBUG_LOG("Failed LockAttributeBuffer");
		return ;
	}

	memcpy(attribute, &Attribute[0], sizeof(DWORD) * Attribute.size());
	(*mesh)->UnlockAttributeBuffer();
	Attribute.clear();

	for (int i = 0; i < VertexCache.size(); ++i)
	{
		CacheEntry* pEntry = VertexCache[i];
		while (pEntry != NULL)
		{
			CacheEntry* pNext = pEntry->pNext;
			SAFE_DELETE(pEntry);
			pEntry = pNext;
		}
	}
	VertexCache.clear();

	Position.clear();
	TexCoord.clear();
	Normal.clear();
}

void OBJLoader::MtlLoad(const string & mtlName)
{

}

DWORD OBJLoader::AddVertex(UINT hash, VERTEX * pVertex)
{
	//DirectX Sample - MeshFromObj 사용함.

	// If this vertex doesn't already exist in the Vertices list, create a new entry.
		// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	DWORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((UINT)VertexCache.size() > hash)
	{
		CacheEntry* pEntry = VertexCache[hash];
		while (pEntry != NULL)
		{
			VERTEX* pCacheVertex = &Vertex[pEntry->index];

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(pVertex, pCacheVertex, sizeof(VERTEX)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = Vertex.size();
		Vertex.push_back(*pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return (DWORD)-1;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		while ((UINT)VertexCache.size() <= hash)
		{
			VertexCache.push_back(NULL);
		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = VertexCache[hash];
		if (pCurEntry == NULL)
		{
			// This is the head element
			//m_VertexCache.SetAt(hash, pNewEntry);
			VertexCache[hash] = pNewEntry;
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}

void OBJLoader::OBJLoad(LPD3DXMESH* mesh, const string & objPath, const string & mapPath)
{

	DWORD dwAttribute = 0;

	ifstream loader;

	loader.open(objPath.c_str());

	if (loader.fail())
	{
		DEBUG_LOG("파일을 여는데 실패 했습니다 : " << objPath.c_str());
		return;
	}

	while (!loader.eof())
	{
		string tag;
		loader >> tag;

		if (tag == "v")
		{
			Vector3 position;
			loader >> position.x >> position.y >> position.z;
			Position.push_back(position);
			continue;
		}
		else if (tag == "vt")
		{
			Vector2 texCoord;
			loader >> texCoord.x >> texCoord.y;
			TexCoord.push_back(texCoord);
			continue;
		}
		else if (tag == "vn")
		{
			Vector3 normal;
			loader >> normal.x >> normal.y >> normal.z;
			Normal.push_back(normal);
			continue;
		}
		else if (tag == "f")
		{
			for (int i = 0; i < 3; ++i)
			{
				string str;
				loader >> str;

				UINT iPosition;
				UINT iTexCoord;
				UINT iNormal;

				sscanf(str.c_str(), "%u/%u/%u", &iPosition, &iTexCoord, &iNormal);

				VERTEX vertex;
				vertex.pos = Position[iPosition - 1];
				vertex.tex = TexCoord[iTexCoord - 1];
				vertex.normal = Normal[iNormal - 1];

				DWORD index = AddVertex(iPosition, &vertex);
				Index.push_back(index);
			}

			Attribute.push_back(dwAttribute);
			continue;
		}
	}

	return CreateMesh(mesh);
}