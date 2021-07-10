#include "DXUT.h"
#include "TileMapManager.h"

TileMapManager::TileMapManager()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			blockss[i][j] = new Sprite;
			blockss[i][j]->SetTexture(L"box.png");
			blockss[i][j]->scale = { 0.5f, 0.5f };

			const Texture* t = blockss[i][j]->GetTexture();


			if (x > (std::size(blockss[i]) - 1))
			{
				x = 0;
				++y;
			}

			blockss[i][j]->SetPosition(
				((blockss[i][j]->scale.x * t->info.Width) / 2) + (x * t->info.Width * blockss[i][j]->scale.x),
				((blockss[i][j]->scale.y * t->info.Height) / 2) + (y * t->info.Height * blockss[i][j]->scale.y));

			++x;
		}
	}
}

void
TileMapManager::CheckMouseCollision()
{
	POINT pnt;
	GetCursorPos(&pnt);
	ScreenToClient(DXUTGetHWND(), &pnt);

	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			if (PtInRect(&blockss[i][j]->GetRect(), pnt))
			{
				blockss[i][j]->SetTexture(L"block.png");
			}
			else
			{
				blockss[i][j]->SetTexture(L"box.png");
			}
		}
	}
}

void
TileMapManager::PlaceBlock(Vec2 position)
{

}

void 
TileMapManager::ChangeBlockType()
{
}

void 
TileMapManager::SaveBlocks()
{
	
}

void 
TileMapManager::LoadBlocks()
{
#if GAMEON == true
	true;
	// 타입이 없는 로드한 블록은 없는 블록으로 건너뛰고, 타입이 있다면 동적할당
#else
	false;
	// 타입이 없는 블록이라도 동적할당. box.png로 텍스처 입히기 
#endif 

}
