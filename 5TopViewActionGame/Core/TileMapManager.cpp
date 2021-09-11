#include "DXUT.h"
#include "Camera.h"
#include "TileMapManager.h"

// 1. ������Ʈ�ʰ� Ÿ�ϸ��� �и��Ǿ�����.
// 2. �и��Ȱ� ���̺�, �ε��ؾ��Ѵ�.
// 3. �и��ǰ� ����� �����Ѵ�.

TileMapManager::TileMapManager() : blockScale(0.5f), currentBlocktype(BlockType::FLOOR)
{
	for (int i = 0; i < std::size(blocks); ++i)
	{
		for (int j = 0; j < std::size(blocks[i]); ++j)
		{
			blocks[i][j] = nullptr;
			objects[i][j] = nullptr;
		}
	}
	walls.push_back(WALL);
	walls.push_back(FLOOR);
}

void 
TileMapManager::Initialize()
{
	int x = 0;
	int y = 0;
	for (int i = 0; i < std::size(blocks); ++i)
	{
		for (int j = 0; j < std::size(blocks[i]); ++j)
		{
			blocks[i][j] = new Block;
			blocks[i][j]->SetTexture(L"box.png");
			blocks[i][j]->scale = { blockScale, blockScale };

			objects[i][j] = new Block;
			objects[i][j]->SetTexture(L"box.png");
			objects[i][j]->scale = { blockScale, blockScale };
			objects[i][j]->layer = 1;
			
			const Texture* t = blocks[i][j]->GetTexture();

			if (x > (std::size(blocks[i]) - 1))
			{
				x = 0;
				++y;
			}

			Vec2 pos = { ((blocks[i][j]->scale.x * t->info.Width) / 2) + (x * t->info.Width * blocks[i][j]->scale.x),
				((blocks[i][j]->scale.y * t->info.Height) / 2) + (y * t->info.Height * blocks[i][j]->scale.y) };

			blocks[i][j]->position = pos;
			objects[i][j]->position = pos;

			++x;

			blocks[i][j]->type = BlockType::NONE;
			objects[i][j]->type = BlockType::NONE;
		}
	}
}

// ��尡 0
// ����°�
// ��尡 1
// ������Ʈ
// �������� ������Ʈ

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

	if (mode == 0)
	{
		for (int i = 0; i < std::size(blocks); ++i)
		{
			for (int j = 0; j < std::size(blocks[i]); ++j)
			{

				if (PtInRect(&blocks[i][j]->GetRect(), pnt))
				{
					if (DXUTIsKeyDown(VK_SPACE))
					{
						if (currentBlocktype == NONE)
						{
							blocks[i][j]->type = currentBlocktype;
						}
						else
						{
							bool ison = false;
							for (auto iter : walls)
								if (iter == currentBlocktype)
								{
									ison = true;
									break;
								}

							if (ison == true)
								blocks[i][j]->type = currentBlocktype;
						}
					}
				}

				blocks[i][j]->SetTexture(GetTextureTag(blocks[i][j]->type));
			}
		}
	}
	else
	{
		for (int i = 0; i < std::size(blocks); ++i)
		{
			for (int j = 0; j < std::size(blocks[i]); ++j)
			{

				if (PtInRect(&objects[i][j]->GetRect(), pnt))
				{
					if (DXUTIsKeyDown(VK_SPACE))
					{
						if (currentBlocktype == NONE)
						{
							objects[i][j]->type = currentBlocktype;
						}
						else
						{
							// �ӽ� ����
							bool ison = true;
							// ���� Ÿ���� ��ȸ�ϸ� ���� �������� �� ���̴�?
							// ���� ������Ʈ���� ����ִµ� Ÿ�ϸ��� �������� �ϸ� �ȵǴϱ�
							// 
							for (auto iter : walls)
								// if iter(���⼭ iter�� ���� ����(��, �� ��)) == ������������ ����̶� ����?
								// ����� ����.
								if (iter == currentBlocktype)
								{
									ison = false;
									break;
								}

							// �׷��� ison false�� �Ǹ� �� ���� �������� �ߴ��Ŵϱ�
							// ����� ����, false�� �ƴϸ� ���� �ƴ϶� ������Ʈ�ϱ� OK
							if (ison == true)
								objects[i][j]->type = currentBlocktype;
						}
					}
				}

				objects[i][j]->SetTexture(GetTextureTag(objects[i][j]->type));
			}
		}
	}
}

std::wstring TileMapManager::GetTextureTag(BlockType type)
{
	switch (type)
	{
	case NONE:
		return L"box.png";
	case FLOOR:
		return L"floor.png";
	case WALL:
		return L"wall.png";
	case PLAYER:
		return L"player (1).png";
	default:
		break;
	}
	return std::wstring();
}

void
TileMapManager::SaveBlocks(const std::string& mapTag)
{
	std::ofstream oin(mapTag);

	for (int i = 0; i < std::size(blocks); ++i)
	{
		for (int j = 0; j < std::size(blocks[i]); ++j)
		{
			int typeValue = (BlockType)blocks[i][j]->type;
			oin << typeValue;
		}
	}

	oin.close();
}

void TileMapManager::SaveObject(const std::string& mapTag)
{
	std::ofstream oin(mapTag);

	for (int i = 0; i < std::size(objects); ++i)
	{
		for (int j = 0; j < std::size(objects[i]); ++j)
		{
			int typeValue = (BlockType)objects[i][j]->type;
			oin << typeValue;
		}
	}

	oin.close();
}

void
TileMapManager::LoadBlocks(const std::string& mapTag)
{
	for (auto& iter : tileBlocks)
		delete iter;
	tileBlocks.clear();

	
	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "������ �����ϴ�." << std::endl;
		return;
	}
	char typeValue;
	int x = 0;
	int y = 0;
	
	while (fin.get(typeValue)) 
	{
		// atoi == char to int
		int chartoint = atoi(&typeValue);
		BlockType type = (BlockType)chartoint;

		if (x > (std::size(blocks[0]) - 1))
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

		block->SetTexture(GetTextureTag(type));

		const Texture* t = block->GetTexture();

		block->SetPosition(
			((block->scale.x * t->info.Width) / 2) + (x * t->info.Width * block->scale.x),
			((block->scale.y * t->info.Height) / 2) + (y * t->info.Height * block->scale.y));

		tileBlocks.push_back(block);

		++x;
	}

	fin.close();
}

void TileMapManager::LoadObject(const std::string& mapTag)
{
	for (auto& iter : objBlocks)
		delete iter;
	objBlocks.clear();


	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "������ �����ϴ�." << std::endl;
		return;
	}
	char typeValue;
	int x = 0;
	int y = 0;

	while (fin.get(typeValue))
	{
		// atoi == char to int
		int chartoint = atoi(&typeValue);
		BlockType type = (BlockType)chartoint;

		if (x > (std::size(objects[0]) - 1))
		{
			x = 0;
			++y;
		}

		if (type == BlockType::NONE ||
			type == PLAYER)
		{
			if (type == PLAYER)
			{
				playerpos =
				{
					((blockScale * 256.f) / 2.f) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2.f) + (y * 256.f * blockScale)
				};
			}
			++x;
			continue;
		}

		Block* block;
		block = new Block();
		block->layer = 1;
		block->type = type;
		block->scale = { blockScale, blockScale };

		block->SetTexture(GetTextureTag(type));

		const Texture* t = block->GetTexture();

		block->SetPosition(
			((block->scale.x * t->info.Width) / 2) + (x * t->info.Width * block->scale.x),
			((block->scale.y * t->info.Height) / 2) + (y * t->info.Height * block->scale.y));

		objBlocks.push_back(block);

		++x;
	}

	fin.close();
}

void TileMapManager::ChangeBlocks()
{
	if (DXUTWasKeyPressed('M'))
	{
		mode = (mode == 0) ? 1 : 0;
		std::cout << mode << std::endl;
	}
	if (DXUTWasKeyPressed(VK_F1))
	{
		currentBlocktype = FLOOR;
	}

	if (DXUTWasKeyPressed(VK_F2))
	{
		currentBlocktype = WALL;
	}

	if (DXUTWasKeyPressed(VK_F3))
	{
		currentBlocktype = PLAYER;
	}
}

void 
TileMapManager::DeleteBlocks()
{
	if (blocks[0] != nullptr)
	{
		for (int i = 0; i < std::size(blocks); ++i)
		{
			for (int j = 0; j < std::size(blocks[i]); ++j)
			{
				delete blocks[i][j];
				blocks[i][j] = nullptr;
				delete objects[i][j];
				objects[i][j] = nullptr;
			}
		}
	}

	for (auto& iter : tileBlocks)
		delete iter;
	for (auto iter : objBlocks)
	{
		delete iter; // �����Ⱚ
		iter = nullptr;
	}
	tileBlocks.clear();
	objBlocks.clear();
}
