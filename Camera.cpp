#include "DXUT.h"
#include "Camera.h"


Camera::Camera()
	:vEyePos(0.f, 0.f, 2.f), vUp(0.f, 1.f, 0.f), vLookAt(0.f, 0.f, 0.f)
{
	float WinSizeX = WINSIZEX;
	float WinSizeY = WINSIZEY;

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, WinSizeX / WinSizeY, 1.f, 1000.f);
	D3DXMatrixLookAtLH(&matView, &vEyePos, &vLookAt, &vUp);

	SetTransform();
}


Camera::~Camera()
{
}

void Camera::SetTransform()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matProj);
	g_device->SetTransform(D3DTS_VIEW, &matView);
}
