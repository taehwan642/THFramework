#include "DXUT.h"
#include "Camera.h"
#include "TileMapManager.h"

TileMapManager::TileMapManager() : blockScale(0.5f), currentBlocktype(BlockType::FLOOR)
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
	ChangeBlocks();
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
					blockTypes[i][j] = currentBlocktype;
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
TileMapManager::SaveBlocks(const std::string& mapTag)
{
	std::ofstream oin(mapTag);

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
TileMapManager::LoadBlocks(const std::string& mapTag)
{
	for (auto& iter : blocks)
		delete iter;
	blocks.clear();

	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}
	float temp = blockScale;
	blockScale = 1;
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

		if (type == BlockType::NONE )
		{
			++x;
			continue;
		}

		Block* block;
		block = new Block();
		block->type = type;
		block->scale = { blockScale, blockScale };

		switch (type)
		{
		case BlockType::NONE:
			block->SetTexture(L"box.png");
			break;
		case BlockType::FLOOR:
			block->SetTexture(L"block.png");
			break;
		case BlockType::OBSTICLE:
			block->SetTexture(L"block2.png");
			break;
		default:
			break;
		}

		const Texture* t = block->GetTexture();

		block->SetPosition(
			((block->scale.x * t->info.Width) / 2) + (x * t->info.Width * block->scale.x),
			((block->scale.y * t->info.Height) / 2) + (y * t->info.Height * block->scale.y));

		blocks.push_back(block);

		++x;
	}

	fin.close();
	blockScale = temp;
}

void TileMapManager::ChangeBlocks()
{
	if (DXUTWasKeyPressed(VK_F1))
	{
		currentBlocktype = BlockType::FLOOR;
	}
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
		delete iter;
	}
	blocks.clear();
}
