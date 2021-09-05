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
			
			case BlockType::OCTOPUS:
			{
				blockss[i][j]->SetTexture(L"octoidle (1).png");
				break;
			}

			case BlockType::PLAYER:
			{
				blockss[i][j]->SetTexture(L"idle (1).png");
				break;
			}

			case BlockType::DOOR:
			{
				blockss[i][j]->SetTexture(L"door1.png");
				break;
			}

			case BlockType::BOSS:
			{
				blockss[i][j]->SetTexture(L"flyidle (1).png");
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
	enemyPos.clear();

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

		if (type == BlockType::NONE ||
			type == BlockType::PLAYER ||
			type == BlockType::OCTOPUS ||
			type == BlockType::DOOR ||
			type == BlockType::BOSS)
		{
			if (type == BlockType::PLAYER)
			{
				playerPos = { ((blockScale * 256.f) / 2) + (x * 256.f * blockScale), 
					((blockScale * 256.f) / 2) + (y * 256.f * blockScale) };
			}
			
			if (type == BlockType::OCTOPUS)
			{
				enemyPos.emplace_back(BlockType::OCTOPUS, Vec2(((blockScale * 256.f) / 2) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2) + (y * 256.f * blockScale)));
			}

			if (type == BlockType::DOOR)
			{
				doorPos = { ((blockScale * 256.f) / 2) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2) + (y * 256.f * blockScale) };
			}

			if (type == BlockType::BOSS)
			{
				enemyPos.emplace_back(BlockType::BOSS, Vec2(((blockScale * 256.f) / 2) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2) + (y * 256.f * blockScale)));
			}
			
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

	if (DXUTWasKeyPressed(VK_F2)) // 플레이어 좌표
	{
		currentBlocktype = BlockType::PLAYER;
	}

	if (DXUTWasKeyPressed(VK_F3)) // 적 좌표
	{
		currentBlocktype = BlockType::OCTOPUS;
	}

	if (DXUTWasKeyPressed(VK_F4))
	{
		currentBlocktype = BlockType::DOOR;
	}

	if (DXUTWasKeyPressed(VK_F5))
	{
		currentBlocktype = BlockType::BOSS;
	}
}

void 
TileMapManager::DeleteBlocks()
{
	if (blockss != nullptr)
	{
		for (int i = 0; i < std::size(blockss); ++i)
		{
			for (int j = 0; j < std::size(blockss[i]); ++j)
			{
				delete blockss[i][j];
			}
		}
	}


	for (auto& iter : blocks)
	{
		delete iter;
	}
	blocks.clear();
}
