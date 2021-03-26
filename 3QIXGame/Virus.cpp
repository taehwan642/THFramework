#include "DXUT.h"
#include "Pixel.h"
#include "Virus.h"

void Virus::SpeedMove()
{
	if (delta <= 0)
	{
		isHit = false;
		pixelpos.first += speedX;
		pixelpos.second += speedY;
		delta = movespeed;
	}
	else
		delta -= DXUTGetElapsedTime();
}

void Virus::BigMove()
{
	if (delta <= 0)
	{
		isHit = false;
		pixelpos.first += speedX;
		pixelpos.second += speedY;
		delta = movespeed;
	}
	else
		delta -= DXUTGetElapsedTime();
}

void Virus::FlashMove()
{
	if (delta <= 0)
	{
		isHit = false;
		pixelpos.first += speedX;
		pixelpos.second += speedY;
		delta = movespeed;
	}
	else
		delta -= DXUTGetElapsedTime();
}

void Virus::ToxinoMove()
{
	if (delta <= 0)
	{
		isHit = false;
		int viruses = 0;
		for (int i = 0; i < VirusManager::GetInstance()->virusVector.size(); ++i)
		{
			if (VirusManager::GetInstance()->virusVector[i]->isactive == false)
				++viruses;
			if (viruses > VirusManager::GetInstance()->virusVector.size() - 4)
			{
				for (int j = 0; j < viruses; ++j)
				{
					ToxinoAbility();
				}
				break;
			}
		}
		pixelpos.first += speedX;
		pixelpos.second += speedY;
		delta = movespeed;
	}
	else
		delta -= DXUTGetElapsedTime();
}

void Virus::CheckCollision()
{
	if (pixelpos.first > 48)
	{
		// movespeed 감소 후 다시 증가
		pixelpos.first = 48;
		SetRandomDirection(direction);
	}
	else if (pixelpos.first < 1)
	{
		// movespeed 감소 후 다시 증가
		pixelpos.first = 1;
		SetRandomDirection(direction);
	}

	if (pixelpos.second > 48)
	{
		pixelpos.second = 48;
		SetRandomDirection(direction);
	}
	else if (pixelpos.second < 1)
	{
		pixelpos.second = 1;
		SetRandomDirection(direction);
	}

	for (int j = virusscale; j >= 0; --j)
	{
		bool check = false;
		if ((pixelpos.first + speedY + j) <= 49)
		{
			if (VirusManager::GetInstance()->pixels[pixelpos.first][pixelpos.second + speedY + j]->state == OBSTICLE ||
				VirusManager::GetInstance()->pixels[pixelpos.first][pixelpos.second + speedY + j]->state == OUTLINE)
			{
				// 가고 있던 방향 바로 앞에 장애물이니까 반대 혹은 다른 방향으로 간다.
				SetRandomDirection(direction);
				check = true;
			}
		}

		if ((pixelpos.first + speedX + j) <= 49)
		{
			if (VirusManager::GetInstance()->pixels[pixelpos.first + speedX + j][pixelpos.second]->state == OBSTICLE ||
				VirusManager::GetInstance()->pixels[pixelpos.first + speedX + j][pixelpos.second]->state == OUTLINE)
			{
				// 가고 있던 방향 바로 앞에 장애물이니까 반대 혹은 다른 방향으로 간다.
				SetRandomDirection(direction);
				check = true;
			}
		}

		if (check == true)
			break;
	}
}

void Virus::SetRandomDirection(VIRUSDIRECTION _direction)
{
	// 1. X 중심일지 Y 중심일지 선택
	// 2. parameter로 들어온 _direction을 제외하고 나머지 3 방향을 골라야함.
	int xory = rand() % 2;
	if (xory == 0) // x 중심
	{
		if (_direction == VLEFT ||
			_direction == VRIGHT)
		{
			if (_direction == VLEFT)
			{
				speedX = 1;
				direction = VRIGHT;
			}
			else
			{
				speedX = -1;
				direction = VLEFT;
			}
		}
		else
		{
			int ran = rand() % 2;
			if (ran == 0)
			{
				speedX = 1;
				direction = VRIGHT;
			}
			else
			{
				speedX = -1;
				direction = VLEFT;
			}
		}
		speedY = 0;
	}
	else // y중심
	{
		if (_direction == VUP ||
			_direction == VDOWN)
		{
			if (_direction == VUP)
			{
				speedY = 1;
				direction = VDOWN;
			}
			else
			{
				speedY = -1;
				direction = VUP;
			}
		}
		else
		{
			int ran = rand() % 2;
			if (ran == 0)
			{
				speedY = 1;
				direction = VDOWN;
			}
			else
			{
				speedY = -1;
				direction = VUP;
			}
		}
		speedX = 0;
	}
}

void Virus::ToxinoAbility()
{
	int x = (rand() % 40) + 5;
	int y = (rand() % 40) + 5;
	int ranTag = rand() % TOXINO;
	if ((VIRUSTAG)ranTag != FLASHVIRUS)
	{
		while (VirusManager::GetInstance()->pixels[x][y]->state == OBSTICLE ||
			VirusManager::GetInstance()->pixels[x][y]->state == OUTLINE)
		{
			x = 5 + (rand() % 40);
			y = 5 + (rand() % 40);

			if (VirusManager::GetInstance()->pixels[x][y]->state != OBSTICLE &&
				VirusManager::GetInstance()->pixels[x][y]->state != OUTLINE)
				break;
		}
	}
	else if ((VIRUSTAG)ranTag == FLASHVIRUS)
	{
		for (int i = 0; i < 50; ++i)
		{
			for (int j = 0; j < 50; ++j)
			{
				if (VirusManager::GetInstance()->pixels[i][j]->state == NONE)
				{
					x = i;
					y = j;
					break;
				}
			}
		}
	}

	VirusManager::GetInstance()->SpawnVirus(VirusManager::GetInstance()->pixels[x][y]->position, x, y, (VIRUSTAG)ranTag);
}

Virus::Virus()
{
	layer = 1;
	SetTexture(L"virus.png");
	scale = { 0.07f, 0.07f };
	direction = VRIGHT;
}

Virus::~Virus()
{

}

void Virus::Update()
{
	CheckCollision();
	switch (tag)
	{
	case SPEEDVIRUS:
		SpeedMove();
		break;
	case BIGVIRUS:
		BigMove();
		break;
	case FLASHVIRUS:
		FlashMove();
		break;
	case TOXINO:
		ToxinoMove();
		break;
	default:
		break;
	}
	position = VirusManager::GetInstance()->pixels[pixelpos.first][pixelpos.second]->position;
}

void VirusManager::SetDifficulty(int _val)
{
	difficulty = _val;
}

void VirusManager::CreateVirus()
{
	for (int i = 0; i < 10; ++i)
	{
		Virus* v = new Virus();
		v->isactive = false;
		virusVector.emplace_back(v);
	}
}

void VirusManager::SpawnVirus(Vec2 _position, int _startX, int _startY, VIRUSTAG _tag)
{
	for (int i = 0; i < virusVector.size(); ++i)
	{
		if (virusVector[i]->isactive == false)
		{
			virusVector[i]->isactive = true;
			virusVector[i]->tag = _tag;
			virusVector[i]->pixelpos.first = _startX;
			virusVector[i]->pixelpos.second = _startY;
			virusVector[i]->position = _position;
			switch (_tag)
			{
			case SPEEDVIRUS:
				virusVector[i]->scale = { 0.1f,0.1f };
				virusVector[i]->virusscale = 0;
				virusVector[i]->movespeed = 0.1f;
				break;
			case BIGVIRUS:
				virusVector[i]->scale = { 0.2f,0.2f };
				virusVector[i]->virusscale = 1;
				virusVector[i]->movespeed = 0.1f;
				break;
			case FLASHVIRUS:
				virusVector[i]->scale = { 0.15f,0.15f };
				virusVector[i]->virusscale = 1;
				virusVector[i]->movespeed = 0.1f;
				break;
			case TOXINO:
				virusVector[i]->scale = { 0.3f,0.3f };
				virusVector[i]->virusscale = 2;
				virusVector[i]->movespeed = 0.1f;
				break;
			default:
				break;
			}
			return;
		}
	}

}

void VirusManager::DeleteVirus()
{
	for (int i = 0; i < virusVector.size(); ++i)
	{
		delete virusVector[i];
	}
	virusVector.clear();
}
