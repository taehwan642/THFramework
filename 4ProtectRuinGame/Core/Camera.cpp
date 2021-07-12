#include "DXUT.h"
#include "Camera.h"

void 
Camera::Update()
{
	D3DXMatrixTranslation(&viewM, -camPos.x, -camPos.y, 0);
	DXUTGetD3D9Device()->SetTransform(D3DTS_VIEW, &viewM);
	
	D3DXMatrixOrthoLH(&projM, screenwidth * camSize, -screenheight * camSize, 0, 1);
	DXUTGetD3D9Device()->SetTransform(D3DTS_PROJECTION, &projM);
}
