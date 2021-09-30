#include "DXUT.h"
#include "AniSprite.h"
#include "Font.h"
#include "Player.h"
#include "UIPack.h"

void UIPack::Init()
{
	background = new AniSprite;
	background->isUI = true;
	background->CreateAnimation(L"Sprites/map/back", 2, 1.1f);
	background->position = MIDDLE;
	background->PlayAnimation(L"Sprites/map/back");

	for (int i = 0; i < 2; ++i)
	{
		buffFont[i] = new Font(2, 1, L"Arial");
		buffFont[i]->position = { 20, (float)i * 60 + 400 };
	}
	//Sprites\ui\ingame\weapon

	for (int i = 0; i < 4; ++i)
	{
		weaponSprite[i] = new Sprite;
		weaponSprite[i]->isUI = true;
		weaponSprite[i]->position = { 30 + (float)i * 100, 600 };
		weaponSprite[i]->scale = { 0.4,0.4 };
	}
	weaponSprite[0]->SetTexture(L"Sprites/ui/ingame/weapon/00.png");
	weaponSprite[1]->SetTexture(L"Sprites/ui/ingame/weapon/01.png");
	weaponSprite[2]->SetTexture(L"Sprites/ui/ingame/weapon/02.png");
	weaponSprite[3]->SetTexture(L"Sprites/ui/ingame/weapon/03.png");
}

void UIPack::Update()
{
	background->PlayAnimation(L"Sprites/map/back");

	if (player->speedbuffTime > 0)
	{
		if (player->speedbuffValue > 0)
		{
			std::string buff;
			buff = "스피드 버프 : ";
			buff += std::to_string(player->speedbuffTime);
			buffFont[0]->SetText((char*)buff.c_str());
		}
	}
	else
		buffFont[0]->SetText(" ");

	if (player->invincibleTime > 0)
	{
		std::string buff;
		buff = "무적 버프 : ";
		buff += std::to_string(player->invincibleTime);
		buffFont[1]->SetText((char*)buff.c_str());
	}
	else
		buffFont[1]->SetText(" ");


	for (int i = 0; i < 4; ++i)
	{
		if (player->currentWeapon == i)
			weaponSprite[i]->color = D3DCOLOR_RGBA(255, 255, 255, 255);
		else
			weaponSprite[i]->color = D3DCOLOR_RGBA(128, 128, 128, 255);
	}
}

void UIPack::Delete()
{
	delete background;
	for (int i = 0; i < 2; ++i)
		delete buffFont[i];

	for (int i = 0; i < 4; ++i)
		delete weaponSprite[i];
}
