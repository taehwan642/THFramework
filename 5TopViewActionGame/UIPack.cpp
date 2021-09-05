#include "DXUT.h"
#include "Sprite.h"
#include "Player.h"
#include "Font.h"
#include "UIPack.h"

void UIPack::Init(Player* p, float* lt)
{
	pl = p;
	plastTime = lt;

	playerhp = new Sprite[pl->maxHP];
	for (int i = 0; i < pl->maxHP; ++i)
	{
		playerhp[i].isUI = true;
		playerhp[i].scale = { 0.3f, 0.3f };
		playerhp[i].position = {100 + ((float)i * 100), 256 * 0.3f};
		playerhp[i].SetTexture(L"heart.png");
	}
	score = new Font(4, 1, L"Arial");
	score->isUI = true;
	score->position = { 0, 150 };
	lastTime = new Font(4, 1, L"Arial");
	lastTime->position = { 0, 350 };
	lastTime->isUI = true;

	hpgauge = new Sprite;
	hpgauge->isUI = true;
	hpgauge->position = { 300,500 };
	hpgauge->SetTexture(L"hpui (1).png");
}

void UIPack::PlayerHPUIUpdate()
{
	for (int i = 0; i < pl->maxHP; ++i)
	{
		playerhp[i].isactive = false;
	}
	for (int i = 0; i < pl->hp; ++i)
	{
		playerhp[i].isactive = true;
	}
}

void UIPack::PlayerScoreUpdate()
{
	score->SetText((char*)std::to_string(pl->score).c_str());
}

void UIPack::SceneLastTimeUpdate()
{
	lastTime->SetText((char*)std::to_string((int)*plastTime).c_str());
}

void UIPack::PlayerHPGaugeUpdate()
{
	std::wstring tag = L"hpui (" + std::to_wstring(pl->hpuigauge + 1) + L").png";
	hpgauge->SetTexture(tag);
}

void UIPack::Update()
{
	PlayerHPUIUpdate();
	PlayerScoreUpdate();
	SceneLastTimeUpdate();
	PlayerHPGaugeUpdate();
}

void UIPack::Delete()
{
	delete[] playerhp;
	delete score;
	delete lastTime;
	delete hpgauge;
}
