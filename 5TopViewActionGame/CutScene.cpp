#include "DXUT.h"
#include "Font.h"
#include "CutScene.h"

void CutScene::Update()
{
}

CutScene::CutScene()
{
	font = new Font(4, 5, L"Arial");

	start = [&]()
	{
		// 검정색에서 본래 색으로 돌아가고, 몇초 뒤 return true

		Vec3 endRGB = { 255, 255, 255 };

		tick += DXUTGetElapsedTime();

		D3DXVec3Lerp(&currentRGB, &currentRGB, &endRGB, DXUTGetElapsedTime() * 2);

		if (fabs(endRGB.x - currentRGB.x) < 1.5f)
		{
			if (tick > 0.5f)
			{
				currentRGB = { 255,255,255 };
				tick = 0.f;
				return true;
			}
		}

		color = D3DCOLOR_RGBA((int)currentRGB.x, (int)currentRGB.y, (int)currentRGB.z, 255);

		return false;
	};

	end = [&]()
	{
		// 검정색에서 본래 색으로 돌아가고, 몇초 뒤 return true
		Vec3 endRGB = { 0, 0, 0 };

		tick += DXUTGetElapsedTime();

		D3DXVec3Lerp(&currentRGB, &currentRGB, &endRGB, DXUTGetElapsedTime() * 2);

		if (fabs(endRGB.x - currentRGB.x) < 1.5f)
		{
			if (tick > 0.5f)
			{
				currentRGB = { 0,0,0};
				tick = 0.f;
				return true;
			}
		}

		color = D3DCOLOR_RGBA((int)currentRGB.x, (int)currentRGB.y, (int)currentRGB.z, 255);

		return false;
	};

}

CutScene::~CutScene()
{
	delete font;
}
