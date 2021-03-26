#include "DXUT.h"
#include "Board.h"

// TODO : 텍스쳐 입히기
// 1. 플레이어 OK
// 2. 앞배경 / 뒷배경 OK
// 아직 클리어가 안됐을 때 그냥 검정색 구름같은게 주변에 떠다니는게 더 나을듯.
// 3. 완전 뒷배경 - 이미지 필요
// 4. 바이러스 1개 또는 4개일때 어떻게 텍스쳐를 구성할지 OK
// 5. 이펙트

void Board::CheckBoard(int _posX, int _posY, int _index)
{
	if (checkedPixels[_posX][_posY] == true)
		return;

	checkedPixels[_posX][_posY] = true;

	if ((pixels[_posX][_posY]->state == CLEARED) ||
		(pixels[_posX][_posY]->state == WALL) ||
		(pixels[_posX][_posY]->state == PATH) ||
		(pixels[_posX][_posY]->state == OUTLINE) ||
		(pixels[_posX][_posY]->state == OBSTICLE))
	{
		return;
	}

	if (_index == 0)
		clear1.emplace_back(pixels[_posX][_posY]);
	else
		clear2.emplace_back(pixels[_posX][_posY]);

	CheckBoard(_posX + 1, _posY, _index);
	CheckBoard(_posX - 1, _posY, _index);
	CheckBoard(_posX, _posY + 1, _index);
	CheckBoard(_posX, _posY - 1, _index);

	return;
}

void Board::SpawnObsticle(int _posX, int _posY, OBSTICLETAG _tag)
{
	switch (_tag)
	{
	case OBRECT:
		pixels[_posX][_posY]->state = OBSTICLE;
		pixels[_posX][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 1][_posY]->state = OBSTICLE;
		pixels[_posX + 1][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX][_posY + 1]->state = OBSTICLE;
		pixels[_posX][_posY + 1]->SetTexture(L"Obsticle.png");
		pixels[_posX + 1][_posY + 1]->state = OBSTICLE;
		pixels[_posX + 1][_posY + 1]->SetTexture(L"Obsticle.png");
		break;
	case OBT:
		pixels[_posX][_posY]->state = OBSTICLE;
		pixels[_posX][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 1][_posY]->state = OBSTICLE;
		pixels[_posX + 1][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 2][_posY]->state = OBSTICLE;
		pixels[_posX + 2][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 1][_posY + 1]->state = OBSTICLE;
		pixels[_posX + 1][_posY + 1]->SetTexture(L"Obsticle.png");
		break;
	case OBI:
		pixels[_posX][_posY]->state = OBSTICLE;
		pixels[_posX][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 1][_posY]->state = OBSTICLE;
		pixels[_posX + 1][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 2][_posY]->state = OBSTICLE;
		pixels[_posX + 2][_posY]->SetTexture(L"Obsticle.png");
		pixels[_posX + 3][_posY]->state = OBSTICLE;
		pixels[_posX + 3][_posY]->SetTexture(L"Obsticle.png");
		break;
	default:
		break;
	}
}

bool Board::CheckPathPlayerAndVirusCollision(std::pair<int, int> _viruspos)
{
	for (auto& it : paths)
	{
		if ((it->indexX == _viruspos.first &&
			it->indexY == _viruspos.second) ||
			(playerX == _viruspos.first &&
				playerY == _viruspos.second))
		{
			if (vim->barriervalue == 1)
			{
				vim->barriervalue = 0;
				return true;
			}

			playerX = pathStartposX;
			playerY = pathStartposY;

			if (vim->immunetime <= 0)
				--vim->HP;

			isCutting = false;
			for (auto& it : paths)
				it->state = NONE;

			paths.clear();
			return true;
		}
	}
	return false;
}

bool Board::CheckPlayerAndVirusCollision(std::pair<int, int> _viruspos)
{
	if ((playerX == _viruspos.first) &&
		(playerY == _viruspos.second))
	{
		if (vim->immunetime <= 0)
			--vim->HP;

		return true;
	}
	return false;
}

bool Board::CheckVirusInClearedArea(Pixel* _pixel, std::pair<int, int> _viruspos)
{
	if ((_pixel->indexX == _viruspos.first) &&
		(_pixel->indexY == _viruspos.second))
	{
		return true;
	}
	return false;
}

void Board::PathstoClearAndSpawnItem(std::list<Pixel*> _list)
{
	// 점수 Cleared된 pixel들의 갯수
	score += _list.size();
	for (auto& it : _list)
	{
		// 안에 바이러스 있는지 없는지 탐색
		for (int i = 0; i < VirusManager::GetInstance()->virusVector.size(); ++i)
		{
			if (VirusManager::GetInstance()->virusVector[i]->isactive == false)
				continue;

			if (VirusManager::GetInstance()->virusVector[i]->tag == TOXINO)
				continue;

			if (CheckVirusInClearedArea(it, VirusManager::GetInstance()->virusVector[i]->pixelpos) == true)
			{
				VirusManager::GetInstance()->virusVector[i]->isactive = false;
			}
		}
		it->state = CLEARED;
	}

	// 일단 전부 다 소진되어있으면
	if (item[0] == 0 &&
		item[1] == 0 &&
		item[2] == 0 &&
		item[3] == 0 &&
		item[4] == 0)
	{
		// 아이템 스폰이 안됨. 따로 띄워주고싶으면 여기다가
	}
	// 랜덤으로 고른 그 아이템이 나올 수 있으면
	// 그게 아니라 아이템이 이미 다 소진되어있으면 다시 돌리기
	else
	{
		int ind = rand() % 5;
		while (item[ind] == 0)
		{
			ind = rand() % 5;
			if (item[ind] != 0)
				break;
		}
		--item[ind];
		// index에 해당하는 아이템 생성
		auto iter = paths.front();
		ItemManager::GetInstance()->SpawnItem(iter->position, iter->indexX, iter->indexY, (ITEMTAG)ind);
	}
	return;
}

void Board::MovePlayer()
{
	if (deltatime <= 0)
	{
		if (DXUTIsKeyDown('W'))
		{
			backposX = playerX;
			backposY = playerY;
			direction = UPDOWN;
			playerY -= 1;
			if (playerY < 0)
				playerY = 0;
			vim->position = pixels[playerX][playerY]->position; // NEW1
			vim->rotation = D3DXToRadian(90); // NEW1
		}
		else if (DXUTIsKeyDown('S'))
		{
			backposX = playerX;
			backposY = playerY;
			direction = UPDOWN;
			playerY += 1;
			if (playerY > 49)
				playerY = 49;
			vim->position = pixels[playerX][playerY]->position; // NEW1
			vim->rotation = D3DXToRadian(270); // NEW1
		}
		else if (DXUTIsKeyDown('A'))
		{
			backposX = playerX;
			backposY = playerY;
			direction = LEFTRIGHT;
			playerX -= 1;
			if (playerX < 0)
				playerX = 0;
			vim->position = pixels[playerX][playerY]->position; // NEW1
			vim->rotation = D3DXToRadian(0); // NEW1
		}
		else if (DXUTIsKeyDown('D'))
		{
			backposX = playerX;
			backposY = playerY;
			direction = LEFTRIGHT;
			playerX += 1;
			if (playerX > 49)
				playerX = 49;
			vim->position = pixels[playerX][playerY]->position; // NEW1
			vim->rotation = D3DXToRadian(180); // NEW1
		}
		deltatime = vim->movementspeed;
	}
	else
	{
		deltatime -= DXUTGetElapsedTime();
	}
}

Board::Board(void)
{
	VirusManager::GetInstance()->CreateVirus(); // NEW1

	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			pixels[i][j] = new Pixel();
			pixels[i][j]->indexX = i;
			pixels[i][j]->indexY = j;
			pixels[i][j]->position =
			{ 300 + ((float)i * 13),
			  20 + ((float)j * 13) };
			pixels[i][j]->state = NONE;
			VirusManager::GetInstance()->pixels[i][j] = pixels[i][j]; // NEW1
		}
	}

	float x = pixels[1][1]->position.x - (pixels[1][1]->texture->info.Width / 2 * pixels[1][1]->scale.x); // NEW2
	float y = pixels[1][1]->position.y - (pixels[1][1]->texture->info.Height / 2 * pixels[1][1]->scale.y); // NEW2

	pivot = { 0, 0 }; // NEW2
	position = { x, y }; // NEW2
	scale = { 1.01f, 1.01f }; // NEW2

	for (int i = 0; i < 50; ++i)
	{
		pixels[i][0]->state = WALL;
		pixels[i][49]->state = WALL;
		pixels[0][i]->state = WALL;
		pixels[49][i]->state = WALL;
	}

	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			checkedPixels[i][j] = false;
		}
	}

	// 200 = 4 * 50 즉 장애물은 총 10개가 적당하다.

	for (int i = 0; i < 10; ++i)
	{
		int x = 4 + (rand() % 41);
		int y = 4 + (rand() % 41);
		int tag = rand() % 3;
		SpawnObsticle(x, y, (OBSTICLETAG)tag);
	}

	vim = new VIM();

	layer = -1; // 신경쓰지말기
	SetTexture(L"desert (1).png"); // 신경쓰지말기 아직까진

	item[0] = 3;
	item[1] = 3;
	item[2] = 1;
	item[3] = 2;
	item[4] = 5;

	ItemManager::GetInstance()->CreateItem();
	
	for (int i = 0; i < 10; ++i) 
	{
		int r = rand() % TOXINO;
		int x = 5 + (rand() % 40);
		int y = 5 + (rand() % 40);
		while (pixels[x][y]->state == OBSTICLE)
		{
			x = 5 + (rand() % 40);
			y = 5 + (rand() % 40); 
			if (pixels[x][y]->state != OBSTICLE)
				break;
		}

		if(i == 0)
			VirusManager::GetInstance()->SpawnVirus(pixels[x][y]->position, pixels[x][y]->indexX, pixels[x][y]->indexY, TOXINO);

		VirusManager::GetInstance()->SpawnVirus(pixels[x][y]->position, pixels[x][y]->indexX, pixels[x][y]->indexY, (VIRUSTAG)r);
	}

	vim->position = pixels[playerX][playerY]->position; // NEW1
}

Board::~Board(void)
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			delete pixels[i][j];
		}
	}
	delete vim;
	ItemManager::GetInstance()->DeleteItem();
	VirusManager::GetInstance()->DeleteVirus();
}

void Board::Update(void)
{
	//std::cout << position.x << " " << position.y << std::endl;
	ItemManager::GetInstance()->CheckItem(playerX, playerY, vim);
	MovePlayer();

	if (isCutting == false && pixels[playerX][playerY]->state == NONE) // 자르기 시작했는지 확인하는 조건문
	{
		// 자르기 시작했다!
		isCutting = true;
		pathStartposX = backposX;
		pathStartposY = backposY;
	}

	if (isCutting == true) // 자르기 시작했다면
	{
		if (pixels[backposX][backposY]->state == NONE) // 만약 다음 픽셀의 state가 NONE이라면
		{
			pixels[backposX][backposY]->state = PATH; // PATH 변경
			pixels[backposX][backposY]->direction = direction;
			paths.emplace_back(pixels[backposX][backposY]);
		}

		// 적이랑 플레이어랑 부딪혔는지 확인
		for (int i = 0; i < VirusManager::GetInstance()->virusVector.size(); ++i)
		{
			if (VirusManager::GetInstance()->virusVector[i]->isactive == false)
				continue;
			if (VirusManager::GetInstance()->virusVector[i]->isHit == true)
				continue;
			if (CheckPathPlayerAndVirusCollision(VirusManager::GetInstance()->virusVector[i]->pixelpos) == true)
			{
				VirusManager::GetInstance()->virusVector[i]->isHit = true;
			}
		}

		// 따로 Path나 Obsticle 이랑 부딪혔다면 (둘이 다시 시작부분으로 되돌아간다는 공통점이 있음.)
		if (pixels[playerX][playerY]->state == PATH || pixels[playerX][playerY]->state == OBSTICLE)
		{
			// HP 깎기
			if (pixels[playerX][playerY]->state == OBSTICLE)
			{
				if (vim->immunetime <= 0)
					--vim->HP;
			}

			playerX = pathStartposX;
			playerY = pathStartposY;
			isCutting = false;

			// PATH 초기화
			for (auto& it : paths)
			{
				it->state = NONE;
			}

			paths.clear();
		}
	}

	if (isCutting == false)
	{
		// 자르지 않는데 장애물이면 그냥 그 방향으로 못가게만 하기
		if (pixels[playerX][playerY]->state == OBSTICLE)
		{
			playerX = backposX;
			playerY = backposY;
		}

		// 자르지 않고있는데 바이러스랑 부딪히는지 확인
		for (int i = 0; i < VirusManager::GetInstance()->virusVector.size(); ++i)
		{
			if (VirusManager::GetInstance()->virusVector[i]->isactive == false)
				continue;
			if (VirusManager::GetInstance()->virusVector[i]->isHit == true)
				continue;
			if (CheckPlayerAndVirusCollision(VirusManager::GetInstance()->virusVector[i]->pixelpos) == true)
			{
				VirusManager::GetInstance()->virusVector[i]->isHit = true;
			}
		}
	}

	// 다 잘랐는지 확인해주는 조건문
	if (isCutting == true && (pixels[playerX][playerY]->state == WALL) || (pixels[playerX][playerY]->state == CLEARED) ||
		(pixels[playerX][playerY]->state == OUTLINE))
	{
		isCutting = false;
		for (auto& it : paths)
		{
			bool check = false;
			if (it->direction == UPDOWN)
			{
				// 양옆이 비어있으면 이 픽셀을 중심으로 탐색
				if ((pixels[it->indexX + 1][it->indexY]->state == NONE) &&
					(pixels[it->indexX - 1][it->indexY]->state == NONE))
				{
					check = true;
				}
			}
			else
			{
				// 위아래가 비어있으면 이 픽셀을 중심으로 탐색
				if ((pixels[it->indexX][it->indexY + 1]->state == NONE) &&
					(pixels[it->indexX][it->indexY - 1]->state == NONE))
				{
					check = true;
				}
			}

			if (check == true)
			{
				if (it->direction == UPDOWN)
				{
					CheckBoard(it->indexX + 1, it->indexY, 0);
					CheckBoard(it->indexX - 1, it->indexY, 1);
				}
				else
				{
					CheckBoard(it->indexX, it->indexY + 1, 0);
					CheckBoard(it->indexX, it->indexY - 1, 1);
				}

				if (clear1.size() > clear2.size()) // 더 작은거 채우기!!
				{
					PathstoClearAndSpawnItem(clear2);
				}
				else
				{
					PathstoClearAndSpawnItem(clear1);
				}

				clear1.clear();
				clear2.clear();

				for (int i = 0; i < 50; ++i)
				{
					for (int j = 0; j < 50; ++j)
					{
						checkedPixels[i][j] = false;
					}
				}
			}
		}

		// 점수 Cleared된 pixel들의 갯수
		score += paths.size();
		for (auto& it : paths)
		{
			it->state = OUTLINE;
		}
		paths.clear();
	}

	// 색 설정
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			switch (pixels[i][j]->state)
			{
			case NONE:
				pixels[i][j]->color = D3DCOLOR_RGBA(255, 255, 255, 200);
				break;
			case WALL:
				pixels[i][j]->color = D3DCOLOR_RGBA(255, 0, 0, 255);
				break;
			case OBSTICLE:
				pixels[i][j]->color = D3DCOLOR_RGBA(255, 255, 255, 255);
				break;
			case PATH:
				pixels[i][j]->color = D3DCOLOR_RGBA(0, 255, 0, 255);
				break;
			case OUTLINE:
				pixels[i][j]->color = D3DCOLOR_RGBA(0, 0, 0, 255);
				break;
			case CLEARED:
				pixels[i][j]->color = D3DCOLOR_RGBA(0, 0, 0, 0);
				break;
			default:
				break;
			}
		}
	}

	if (showplayerpos == true)
		pixels[playerX][playerY]->color = D3DCOLOR_RGBA(100, 100, 100, 255);

	for (auto& it : paths)
	{
		if (it->direction == UPDOWN)
		{
			it->color = D3DCOLOR_RGBA(0, 0, 255, 255);
		}
		else
		{
			it->color = D3DCOLOR_RGBA(200, 200, 0, 255);
		}
	}

	// 색 설정
	/*for (int i = 0; i < VirusManager::GetInstance()->virusVector.size(); ++i)
	{
		if (VirusManager::GetInstance()->virusVector[i]->isactive == false)
			continue;

		for (int j = 0; j < VirusManager::GetInstance()->virusVector[i]->pixelpos.size(); ++j)
		{
			pixels[VirusManager::GetInstance()->virusVector[i]->pixelpos[j].first]
				[VirusManager::GetInstance()->virusVector[i]->pixelpos[j].second]->color = D3DCOLOR_RGBA(128, 0, 128, 255);
		}
	}*/

	// 디버그
	if (DXUTWasKeyPressed('L'))
		showplayerpos = !showplayerpos;

	if (DXUTWasKeyPressed('O'))
	{
		std::cout << "----" << std::endl;
		for (int i = 0; i < 5; ++i)
			std::cout << i << " " << item[i] << std::endl;
		std::cout << "----" << std::endl;
	}

	// 클리어 조건 충족했는지 확인
	if (score >= 2000) //장애물은 2500개의 픽셀들 속에서 500개 미만이어야함.
	{
		std::cout << "CLEAR" << std::endl;
	}

	// 플레이어가 죽었는지 확인
	if (vim->HP <= 0)
	{
		std::cout << "DEAD" << std::endl;
	}

	//std::cout << vim->HP << std::endl;


	// 1. 무적
	if (DXUTWasKeyPressed(VK_F1))
		vim->immunetime = FLT_MAX;
	// 2. 아이템 랜덤 사용
	if (DXUTWasKeyPressed(VK_F2))
	{
		int ind = rand() % 5;
		ItemManager::GetInstance()->SpawnItem
		(pixels[playerX + 1][playerY]->position, playerX + 1, playerY, (ITEMTAG)ind);
	}
	// 3. 생명력 증가
	if (DXUTWasKeyPressed(VK_F3))
	{
		++vim->HP;
	}
	// 5. 1스테이지 전환
	if (DXUTWasKeyPressed(VK_F5))
	{

	}
	// 6. 2스테이지 전환
	if (DXUTWasKeyPressed(VK_F6))
	{

	}
}

void Board::SetDifficulty(int _val)
{
	difficulty = _val;
	VirusManager::GetInstance()->SetDifficulty(_val);
}
