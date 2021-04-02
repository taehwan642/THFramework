#include "DXUT.h"
#include "Camera.h"

void Camera::CameraInit()
{
	D3DXMatrixIdentity(&WM); // 월드 행렬 초기화 (단위 행렬로 바꿔줌)
}

void Camera::CameraUpdate()
{
	D3DXMATRIX translation;
	D3DXMatrixTranslation(&translation, -cameraPos.x, -cameraPos.y, 0);
	D3DXMATRIX rotation;
	D3DXMatrixRotationZ(&rotation, cameraRot);
	
	VM = translation * rotation;

	D3DXMatrixOrthoLH(&PM, ScreenW * cameraSize, -ScreenH * cameraSize, 0, 1);

	DEVICE->SetTransform(D3DTS_WORLD, &WM);
	DEVICE->SetTransform(D3DTS_VIEW, &VM);
	DEVICE->SetTransform(D3DTS_PROJECTION, &PM);
}
