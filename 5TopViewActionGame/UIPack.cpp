#include "DXUT.h"
#include "Sprite.h"
#include "Player.h"
#include "Font.h"
#include "AniSprite.h"
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
		playerhp[i].layer = 999;
	}
	score = new Font(4, 1, L"Arial");
	score->layer = 999;
	score->isUI = true;
	score->position = { 0, 150 };
	lastTime = new Font(4, 1, L"Arial");
	lastTime->position = { 0, 350 };
	lastTime->layer = 999;
	lastTime->isUI = true;

	hpgauge = new Sprite;
	hpgauge->isUI = true;
	hpgauge->layer = 999;
	hpgauge->position = { 300,500 };
	hpgauge->SetTexture(L"hpui (1).png");

	sea = new AniSprite;
	sea->CreateAnimation(L"sea", 6, 1.0f);
	sea->PlayAnimation(L"sea");
	sea->layer = -100;
	sea->position = { screenwidth / 2, screenheight / 2 };
	sea->isUI = true;

	attackgaugeOutline = new Sprite;
	attackgaugeOutline->layer = 999;
	attackgaugeOutline->isUI = true;
	attackgaugeOutline->scale = {0.5f,0.5f};
	attackgaugeOutline->position = { 1000, 80 };
	attackgaugeOutline->SetTexture(L"gaugeUI.png");
	
	attackgaugeBar = new AniSprite;
	attackgaugeBar->layer = 998;
	attackgaugeBar->isUI = true;
	attackgaugeBar->scale = { 0.5f,0.5f };
	attackgaugeBar->position = { 1000, 80 };
	attackgaugeBar->SetTexture(L"gaugeUIBar (1).png");
	attackgaugeBar->CreateAnimation(L"gaugeUIBar", 4, 0.2f);

	aim = new Sprite;
	aim->layer = 999;
	aim->scale = { 0.5f,0.5f };
	aim->position = { -999,-999 };
	aim->SetTexture(L"aim.png");

	scoreboard = new Sprite;
	scoreboard->layer = 1000;
	scoreboard->isUI = true;
	scoreboard->position = { screenwidth / 2,screenheight / 2 };
	scoreboard->SetTexture(L"scoreboard.png");
	scoreboard->isactive = false;

	scorefont = new Font(4, 1, L"Arial");
	scorefont->layer = 1001;
	scorefont->position = { screenwidth / 2,screenheight / 2 - 100 };
	scorefont->isactive = false;
	scorefont->color = D3DCOLOR_RGBA(0, 0, 0, 255);
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

void UIPack::AttackGaugeBarUpdate()
{
	attackgaugeBar->PlayAnimation(L"gaugeUIBar");
	if (pl->attackgauge > 10)
		pl->attackgauge = 10;
	float x = attackgaugeBar->GetTexture()->info.Width * (pl->attackgauge / 10.f);
	// 10으로 차면 공격 가능하게
	
	SetRect(&attackgaugeBar->imgRect, 0, 0, (int)x, attackgaugeBar->GetTexture()->info.Height);
}

void UIPack::ScoreBoardUpdate()
{
	// isdead가 트루면 isactive도 true. 당연하다!
	scoreboard->isactive = pl->isdead;
	scorefont->isactive = pl->isdead;
	scorefont->SetText((char*)std::to_string(pl->score).c_str());
}

void UIPack::Update()
{
	aim->position = pl->aimPos;
	sea->PlayAnimation(L"sea");

	PlayerHPUIUpdate();
	PlayerScoreUpdate();
	SceneLastTimeUpdate();
	PlayerHPGaugeUpdate();
	AttackGaugeBarUpdate();
	ScoreBoardUpdate();
}

void UIPack::Delete()
{
	delete[] playerhp;
	delete score;
	delete lastTime;
	delete hpgauge;
	delete sea;
	delete attackgaugeOutline;
	delete attackgaugeBar;
	delete aim;
	delete scoreboard;
	delete scorefont;
}
