#pragma once

class Camera;
class ModelViewer;

class MainGame
{
private:
	Camera * camera;
	ModelViewer * viewer;
public:
	MainGame();
	virtual ~MainGame();

	void Init();
	void Release();
	void Update();
	void Render();
};

