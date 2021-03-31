#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	b = new Board;
	b->SetDifficulty(1);
	back = new Sprite();
	back->position = { ScreenW / 2, ScreenH / 2 };
	back->layer = -3;
	back->SetTexture(L"background.png");
	font = new Font();
	font->layer = 10;
	font->Createfont(5, 5, L"Arial");
	font->SetFont("Press R to Restart\nPress E to view RankingScene");
	font->isactive = false;

	panel = new Sprite();
	panel->position = { ScreenW / 2, ScreenH / 2 };
	panel->layer = 8;
	panel->SetTexture(L"Pixel.png");
	panel->scale = { 1.5f,2.f };
	panel->isactive = false;

	score = new Font();
	score->layer = 9;
	score->Createfont(2, 2, L"Arial");
	score->SetFont("Score :");
	score->color = D3DCOLOR_RGBA(0, 0, 0, 255);
	score->position = {469, 132 };
	score->isactive = false;
	Director::GetInstance()->isgameend = false;
}

void GameScene::Update()
{
	if (b->score >= 2000 && b->boardclear < 0) //장애물은 2500개의 픽셀들 속에서 500개 미만이어야함.
	{
		b->vim->immunetime = FLT_MAX;
		// 결과창 띄워주고
		// 몇 초 뒤 또는 특정 버튼을 입력하면 넘어감
		score->isactive = true;
		panel->isactive = true;
		string a;
		a = "Score : " + to_string(b->score) + " + " + to_string(b->vim->vimscore) + "\nNext Stage = ENTER";
		score->SetFont((char*)a.c_str());
		
		if (DXUTWasKeyPressed(VK_RETURN))
		{
			int difficulty = b->difficulty;
			if (difficulty == 1)
			{
				Director::GetInstance()->latestScore += b->score + b->vim->vimscore;
				delete b;
				b = new Board();
				b->SetDifficulty(difficulty + 1);
				score->isactive = false;
				panel->isactive = false;
			}
			else
			{
				Director::GetInstance()->latestScore += b->score + b->vim->vimscore;
				Director::GetInstance()->isgameend = true;
				Director::GetInstance()->ChangeScene(RANKINGSCENE);
				return;
			}
		}
	}

	if (b->vim->HP <= 0 || b->cleartime < 0)
	{
		font->isactive = true;
		// 이어하던지, 아님 랭킹으로 가던지
		if (DXUTWasKeyPressed('R'))
		{
			int difficulty = b->difficulty;
			delete b;
			b = new Board;
			b->SetDifficulty(difficulty);
			font->isactive = false;
		}
		else if (DXUTWasKeyPressed('E'))
		{
			Director::GetInstance()->ChangeScene(RANKINGSCENE);
			return;
		}
	}

	// 5. 1스테이지 전환
	if (DXUTWasKeyPressed(VK_F5))
	{
		delete b;
		b = new Board();
		b->SetDifficulty(1);
	}
	// 6. 2스테이지 전환
	if (DXUTWasKeyPressed(VK_F6))
	{
		delete b;
		b = new Board();
		b->SetDifficulty(2);
	}

	// 4. 메뉴 전환
	if (DXUTWasKeyPressed(VK_F4))
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
	}
}

void GameScene::Exit()
{
	delete panel;
	delete score;
	delete b;
	delete back;
	delete font;
}
