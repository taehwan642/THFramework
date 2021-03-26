#include "DXUT.h"
#include "Pixel.h"

Pixel::Pixel(void)
{
	int ran = (rand() % 3) + 1;
	std::wstring result = L"infected" + to_wstring(ran) + L".png";
	SetTexture(result);

	scale = { 0.05f,0.05f };
}

Pixel::~Pixel(void)
{
}

void Pixel::Update(void)
{
	
}