#include "DXUT.h"
#include "MenuScene.h"

void 
MenuScene::Init()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < std::size(block); ++i)
	{
		block[i] = new Sprite;
		block[i]->SetTexture(L"block.png");
		block[i]->scale = { 0.5f, 0.5f };

		const Texture* t = block[i]->GetTexture();


		if (x > 9)
		{
			x = 0;
			++y;
		}

		block[i]->SetPosition(
			((block[i]->scale.x * t->info.Width) / 2) + (x * t->info.Width * block[i]->scale.x),
			((block[i]->scale.y * t->info.Height) / 2) + (y * t->info.Height * block[i]->scale.y));
	
		++x;
	}
}

void 
MenuScene::Update()
{
}

void 
MenuScene::Exit()
{
	for (int i = 0; i < std::size(block); ++i)
	{
		delete block[i];
	}
}
