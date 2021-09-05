#include "DXUT.h"
#include "Sprite.h"
#include "Player.h"
#include "Font.h"
#include "UIPack.h"

void UIPack::Init(Player* p, float* lt)
{
	pl = p;
	plastTime = lt;
	for (int i = 0; i < PLAYERMAXHP; ++i)
	{
		playerhp[i] = new Sprite;
		playerhp[i]->scale = { 0.3f, 0.3f };
		playerhp[i]->position = {100 + ((float)i * 100), 256 * 0.3f};
		playerhp[i]->SetTexture(L"heart.png");
	}
	score = new Font(4, 1, L"Arial");
	score->position = { 0, 150 };
	lastTime = new Font(4, 1, L"Arial");
	lastTime->position = { 0, 350 };
}

void UIPack::PlayerHPUIUpdate()
{
	for (int i = 0; i < PLAYERMAXHP; ++i)
	{
		playerhp[i]->isactive = false;
	}
	for (int i = 0; i < pl->hp; ++i)
	{
		playerhp[i]->isactive = true;
	}
}

void UIPack::PlayerScoreUpdate()
{
	score->SetText((char*)std::to_string(pl->score).c_str());
	lastTime->SetText((char*)std::to_string((int)*plastTime).c_str());
}

void UIPack::Update()
{
	PlayerHPUIUpdate();
	PlayerScoreUpdate();
}

void UIPack::Delete()
{
	for (int i = 0; i < PLAYERMAXHP; ++i)
		delete playerhp[i];
	delete score;
	delete lastTime;
}
