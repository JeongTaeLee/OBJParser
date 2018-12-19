#pragma once
#include "OBJLoader.h"

class ModelViewer
{
private:
	OBJLoader loader;
	Mesh * Model;
	
	Vector3 vRot;
	Matrix matWorld;
public:
	ModelViewer();
	~ModelViewer();

	void InitModel(const string & objPath, const string & mapPath = "None");
	void Update();
	void ModelRender();

	void SetTransform();
};

