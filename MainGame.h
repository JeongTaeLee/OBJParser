#pragma once

class Camera;

class MainGame
{
private:
	Camera * camera;
	LPD3DXMESH mesh;
public:
	MainGame();
	virtual ~MainGame();

public:
	void Init();
	void Release();
	void Update();
	void Render();
};

