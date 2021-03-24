#include "DXUT.h"
#include "VIM.h"

VIM::VIM()
{
	layer = -1;
	SetTexture(L"Pixel.png");
}

VIM::~VIM()
{
}

void VIM::Update()
{
	immunetime -= DXUTGetElapsedTime();
}
