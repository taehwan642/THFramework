#include "DXUT.h"
#include "VIM.h"

VIM::VIM()
{
	layer = 3;
	scale = { 0.3f, 0.3f };
	SetTexture(L"bluePlayer (1).png");
}

VIM::~VIM()
{
}

void VIM::Update()
{
	immunetime -= DXUTGetElapsedTime();

	switch (HP)
	{
	case 5:
		Animation(L"bluePlayer", 0.1f, 6);
		break;
	case 4:
		Animation(L"mintPlayer", 0.1f, 6);
		break;
	case 3:
		Animation(L"greenPlayer", 0.1f, 6);
		break;
	case 2:
		Animation(L"yellowPlayer", 0.1f, 6);
		break;
	case 1:
		Animation(L"orangePlayer", 0.1f, 6);
		break;
	default:
		break;
	}
}
