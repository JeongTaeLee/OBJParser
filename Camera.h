#pragma once
class Camera
{
private:
	Vector3 vEyePos;
	Vector3 vUp;
	Vector3 vLookAt;

	Matrix matView;
	Matrix matProj;
public:
	Camera();
	 ~Camera();
	
	 void SetTransform();
};

