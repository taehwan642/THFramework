#include "DXUT.h"
#include "Camera.h"
#include "TileMapManager.h"

TileMapManager::TileMapManager() : blockScale(0.5f)
{
	
}

void 
TileMapManager::Initialize()
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
TileMapManager::UpdateManager()
{
	POINT pnt;
	GetCursorPos(&pnt);
	ScreenToClient(DXUTGetHWND(), &pnt);

	Camera& cam = Camera::GetInstance();
	Vec2 camPos = cam.GetPosition();
	pnt.x = (camPos.x - screenwidth / 2) + pnt.x;
	pnt.y = (camPos.y - screenheight / 2) + pnt.y;

	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{

			if (PtInRect(&blockss[i][j]->GetRect(), pnt))
			{
				if (DXUTIsKeyDown(VK_SPACE))
				{
					blockTypes[i][j] = BlockType::FLOOR;
				}
			}

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
	std::ofstream oin("map.txt");

	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			int typeValue = static_cast<int>(blockTypes[i][j]);
			oin << std::to_string(typeValue);
		}
	}

	oin.close();
}

void
TileMapManager::LoadBlocks()
{
	std::ifstream fin("map.txt");
	if (fin.fail())
	{
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}

	char typeValue;
	int x = 0;
	int y = 0;
	while (fin.get(typeValue)) 
	{
		int chartoint = atoi(&typeValue);
		BlockType type = static_cast<BlockType>(chartoint);

		if (x > (std::size(blockss[0]) - 1))
		{
			x = 0;
			++y;
		}

#if GAMEON == true
		if (type == BlockType::NONE)
		{
			++x;
			continue;
		}
#endif 
		Block block;
		block.type = type;
		block.sprite = new Sprite();
		block.sprite->scale = { blockScale, blockScale };

		switch (type)
		{
		case BlockType::NONE:
			block.sprite->SetTexture(L"box.png");
			break;
		case BlockType::FLOOR:
			block.sprite->SetTexture(L"block.png");
			break;
		case BlockType::OBSTICLE:
			block.sprite->SetTexture(L"block2.png");
			break;
		default:
			break;
		}

		const Texture* t = block.sprite->GetTexture();

		block.sprite->SetPosition(
			((block.sprite->scale.x * t->info.Width) / 2) + (x * t->info.Width * block.sprite->scale.x),
			((block.sprite->scale.y * t->info.Height) / 2) + (y * t->info.Height * block.sprite->scale.y));

		blocks.push_back(block);

		++x;
	}

	fin.close();
}

void 
TileMapManager::DeleteBlocks()
{
	for (int i = 0; i < std::size(blockss); ++i)
	{
		for (int j = 0; j < std::size(blockss[i]); ++j)
		{
			delete blockss[i][j];
		}
	}

	for (auto& iter : blocks)
	{
		delete iter.sprite;
	}
}
