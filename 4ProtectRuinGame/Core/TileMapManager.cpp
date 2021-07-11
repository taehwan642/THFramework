#include "DXUT.h"
#include "TileMapManager.h"

TileMapManager::TileMapManager() : blockScale(0.5f)
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			blockss[i][j] = new Sprite;
			blockss[i][j]->SetTexture(L"box.png");
			blockss[i][j]->scale = { blockScale, blockScale };

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

			blockTypes[i][j] = BlockType::NONE;
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
				if (DXUTIsMouseButtonDown(VK_LEFT))
				{
					blockTypes[i][j]= BlockType::FLOOR;
				}
			}
		}
	}
}

void
TileMapManager::ChangeBlockType()
{
}

void
TileMapManager::UpdateManager()
{
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			switch (blockTypes[i][j])
			{
			case BlockType::NONE: 
			{
				blockss[i][j]->SetTexture(L"box.png");
				break; 
			}
			
			case BlockType::FLOOR: 
			{
				blockss[i][j]->SetTexture(L"block.png");
				break; 
			}
			
			case BlockType::OBSTICLE: 
			{
				break; 
			}
			
			default:
				break;
			}
		}
	}
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

	std::ifstream fin("map.txt");
	if (fin.fail())
	{
		std::cout << "파일이 없습니다. 새로 만듭니다." << std::endl;
		
	}
	// 한줄씩 읽기
	// 그 줄에 해당하는 타입을 읽고, NONE 타입이라면 넘기기
	// NONE 타입이 아니라면 큐브 만들고 배치.

	fin.close();
}

void TileMapManager::DeleteBlocks()
{
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			delete blockss[i][j];
		}
	}
}
