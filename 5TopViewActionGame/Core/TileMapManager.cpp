#include "DXUT.h"
#include "Camera.h"
#include "TileMapManager.h"

// 1. 오브젝트맵과 타일맵은 분리되어있음.
// 2. 분리된걸 세이브, 로드해야한다.
// 3. 분리되게 블록을 찍어야한다.

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
	walls.push_back(FLOOR);

	walls.push_back(WALL1);
	walls.push_back(WALL2);
	walls.push_back(WALL3);
	walls.push_back(WALL4);

	walls.push_back(CORNER1);
	walls.push_back(CORNER2);
	walls.push_back(CORNER3);
	walls.push_back(CORNER4);
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

// 모드가 0
// 맵찍는거
// 모드가 1
// 오브젝트
// 맵찍을때 오브젝트

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
							// 임시 변수
							bool ison = true;
							// 벽의 타입을 순회하며 현재 찍으려는 게 벽이다?
							// 현재 오브젝트맵을 찍고있는데 타일맵을 찍으려고 하면 안되니까
							// 
							for (auto iter : walls)
								// if iter(여기서 iter는 맵의 종류(벽, 땅 등)) == 지금찍으려는 블록이랑 같다?
								// 못찍게 막기.
								if (iter == currentBlocktype)
								{
									ison = false;
									break;
								}

							// 그래서 ison false가 되면 난 벽을 찍으려고 했던거니까
							// 못찍게 막고, false가 아니면 벽이 아니라 오브젝트니까 OK
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
	case WALL1:
		return L"wall.png";
	case WALL2:
		return L"wall2.png";
	case WALL3:
		return L"wall3.png";
	case WALL4:
		return L"wall4.png";
	case CORNER1:
		return L"corner.png";
	case CORNER2:
		return L"corner2.png";
	case CORNER3:
		return L"corner3.png";
	case CORNER4:
		return L"corner4.png";
	case DOOR1:
		return L"door.png";
	case DOOR2:
		return L"door2.png";
	case DOOR3:
		return L"door3.png";
	case DOOR4:
		return L"door4.png";
	case WINDOW1:
		return L"window.png";
	case WINDOW2:
		return L"window2.png";
	case CHEST:
		return L"chest (1).png";
	case PLAYER:
		return L"player (1).png";
	case MONSTER1:
		return L"m1idle (1).png";
	case MONSTERSPAWNER:
		return L"MonsterSpawner.png";
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
			oin << typeValue << '\n';
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
			oin << typeValue << '\n';
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
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}
	int x = 0;
	int y = 0;

	while (!fin.eof()) 
	{
		char arr[256];
		fin.getline(arr, 256);
		int chartoint = atoi(arr);
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
	chestpos.clear();
	monsterpos.clear();

	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}

	int x = 0;
	int y = 0;

	while (!fin.eof())    //파일 끝까지 읽었는지 확인
	{
		char arr[256];

		fin.getline(arr, 256);    //한줄씩 읽어오기

		int chartoint = atoi(arr);
		BlockType type = (BlockType)chartoint;

		if (x > (std::size(objects[0]) - 1))
		{
			x = 0;
			++y;
		}

		if (type == BlockType::NONE ||
			type == PLAYER ||
			type == CHEST ||
			(type >= DOOR1 && type <= DOOR4) ||
			type >= MONSTER1)
		{
			if (type == PLAYER)
			{
				playerpos =
				{
					((blockScale * 256.f) / 2.f) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2.f) + (y * 256.f * blockScale)
				};
			}

			if (type == CHEST)
			{
				Vec2 c =
				{
					((blockScale * 256.f) / 2.f) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2.f) + (y * 256.f * blockScale)
				};
				chestpos.push_back(c);
			}

			if (type == MONSTER1 || type == MONSTERSPAWNER)
			{
				Vec2 c =
				{
					((blockScale * 256.f) / 2.f) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2.f) + (y * 256.f * blockScale)
				};
				MonsterTag tag;
				tag.position = c;
				tag.type = type;
				monsterpos.push_back(tag);
			}

			if ((type >= DOOR1 && type <= DOOR4))
			{
				doortag.pos =
				{
					((blockScale * 256.f) / 2.f) + (x * 256.f * blockScale),
					((blockScale * 256.f) / 2.f) + (y * 256.f * blockScale)
				};
				doortag.doortype = type;
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

void TileMapManager::UpdateBlocks(const std::string& mapTag)
{
	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}
	int x = 0;
	int y = 0;

	while (!fin.eof()) 
	{
		char arr[256];
		fin.getline(arr, 256);
		int chartoint = atoi(arr);

		BlockType type = (BlockType)chartoint;

		if (x > (std::size(blocks[0]) - 1))
		{
			x = 0;
			++y;
		}

		if (y != 6)
		{
			blocks[y][x]->SetTexture(GetTextureTag(type));
			blocks[y][x]->type = type;
		}

		++x;
	}

	fin.close();
}

void TileMapManager::UpdateObject(const std::string& mapTag)
{
	std::ifstream fin(mapTag);
	if (fin.fail())
	{
		std::cout << "파일이 없습니다." << std::endl;
		return;
	}
	int x = 0;
	int y = 0;

	while (!fin.eof())
	{
		char arr[256];
		fin.getline(arr, 256);
		int chartoint = atoi(arr);
		BlockType type = (BlockType)chartoint;

		if (x > (std::size(blocks[0]) - 1))
		{
			x = 0;
			++y;
		}

		if (y != 6)
		{
			objects[y][x]->SetTexture(GetTextureTag(type));
			objects[y][x]->type = type;
		}


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
		currentBlocktype = NONE;
	}

	if (DXUTWasKeyPressed(VK_F2))
	{
		currentBlocktype = FLOOR;
	}

	if (DXUTWasKeyPressed(VK_F3))
	{
		if (count > 3)
		{
			count = 0;
		}
		currentBlocktype = (BlockType)(WALL1 + count);
		++count;
	}

	if (DXUTWasKeyPressed(VK_F4))
	{
		if (count > 3)
		{
			count = 0;
		}
		currentBlocktype = (BlockType)(CORNER1 + count);
		++count;
	}

	if (DXUTWasKeyPressed(VK_F5))
	{
		if (count > 3)
		{
			count = 0;
		}
		currentBlocktype = (BlockType)(DOOR1 + count);
		++count;
	}

	if (DXUTWasKeyPressed(VK_F6))
	{
		if (count > 1)
		{
			count = 0;
		}
		currentBlocktype = (BlockType)(WINDOW1 + count);
		++count;
	}

	if (DXUTWasKeyPressed(VK_F7))
	{
		currentBlocktype = CHEST;
	}

	if (DXUTWasKeyPressed(VK_F8))
	{
		currentBlocktype = PLAYER;
	}

	if (DXUTWasKeyPressed(VK_F9))
	{
		if (count > 4)
		{
			count = 0;
		}
		currentBlocktype = MONSTER1;
		//currentBlocktype = (BlockType)(MONSTER1 + count);
		++count;
	}

	if (DXUTWasKeyPressed(VK_F10))
	{
		currentBlocktype = MONSTERSPAWNER;
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
		delete iter; // 쓰레기값
		iter = nullptr;
	}
	tileBlocks.clear();
	objBlocks.clear();
}
