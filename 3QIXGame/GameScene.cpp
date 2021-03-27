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
	font->SetFont("Press R to Restart");
	font->isactive = false;
}

void GameScene::Update()
{
	// 클리어 조건 충족했는지 확인
	if (b->score >= 2000) //장애물은 2500개의 픽셀들 속에서 500개 미만이어야함.
	{
		int difficulty = b->difficulty;
		delete b;
		b = new Board();
		b->SetDifficulty(difficulty + 1);
	}

	if (b->vim->HP <= 0)
	{
		font->isactive = true;
		if (DXUTWasKeyPressed('R'))
		{
			int difficulty = b->difficulty;
			delete b;
			b = new Board;
			b->SetDifficulty(difficulty);
			font->isactive = false;
		}
	}

	// 4. 메뉴 전환
	if (DXUTWasKeyPressed(VK_F4))
	{
		Director::GetInstance()->ChangeScene(MENUSCENE);
		return;
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
}

void GameScene::Exit()
{
	delete b;
	delete back;
	delete font;
}
