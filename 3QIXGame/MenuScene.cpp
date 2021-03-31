#include "DXUT.h"
#include "GameScene.h"
#include "MenuScene.h"

void MenuScene::Init()
{
	for (int i = 0; i < 5; ++i)
	{
		buttons[i] = new Sprite();
		buttons[i]->position = { ScreenW / 2, 200 + ((float)i) * 100 };
		buttons[i]->scale = { 0.3f,0.3f };
	}
	buttons[0]->SetTexture(L"gamestart.png");
	buttons[1]->SetTexture(L"howtoplay.png");
	buttons[2]->SetTexture(L"about.png");
	buttons[3]->SetTexture(L"score.png");
	buttons[4]->SetTexture(L"credit.png");

	
	about = new Sprite();
	about->position = { ScreenW / 2, ScreenH / 2 };
	about->scale = { 4,2 };
	about->layer = 3;
	about->SetTexture(L"Pixel.png");
	about->isactive = false;

	exitabout = new Sprite();
	exitabout->position = { 1088, 156 };
	exitabout->scale = { 0.3,0.3 };
	exitabout->layer = 5;
	exitabout->SetTexture(L"Pixel.png");
	exitabout->isactive = false;

	for (int i = 0; i < 4; ++i)
	{
		items[i] = new Sprite();
		items[i]->scale = { 0.5f,0.5f };
		items[i]->layer = 4;
		items[i]->SetTexture(L"Pixel.png");
		items[i]->position = { ScreenW / 2, ScreenH / 2 };
		items[i]->isactive = false;

		aboutfont[i] = new Font();
		aboutfont[i]->layer = 4;
		aboutfont[i]->Createfont(1.3f, 3, L"Arial");
		aboutfont[i]->SetFont("이건 힙합입니다");
		aboutfont[i]->color = D3DCOLOR_RGBA(0, 0, 0, 255);
		aboutfont[i]->isactive = false;
	}

	items[0]->position = { 269, 224 };
	items[1]->position = { 269, 501 };
	items[2]->position = { 736, 224 };
	items[3]->position = { 736, 501 };
	aboutfont[0]->position = { 369, 170 };
	aboutfont[1]->position = { 369, 443 };
	aboutfont[2]->position = { 836, 170 };
	aboutfont[3]->position = { 836, 443 };

	aboutexamples.emplace_back(L"virus.png", "이건 바이러스입니다 우와!");
	aboutexamples.emplace_back(L"virus2.png", "이것도 바이러스입니다\n완전쎄서 다들 무서워해요");
	aboutexamples.emplace_back(L"toxino (1).png", "보스입니다\n맨처음에 포효하고 공격을\n시작합니다");
	aboutexamples.emplace_back(L"mintItem.png", "몬스터같죠? 아이템입니다");

	aboutexamples.emplace_back(L"orangeItem.png", "이것도 아이템이에오\n근데 뭔효과인지 몰겠음");
	aboutexamples.emplace_back(L"Obsticle.png", "얘는 장애물이에요");
	aboutexamples.emplace_back(L"yellowItem.png", "얘도 사실 잘 모르겠어요");
	aboutexamples.emplace_back(L"blueItem.png", "얘도 마찬가지인것같아요");

	currentIndex = 0;
	maxIndex = 1;
}

void MenuScene::Update()
{
	if (DXUTIsMouseButtonDown(VK_LEFT))
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(DXUTGetHWND(), &p);
		if (exitabout->isactive == true && PtInRect(&exitabout->GetRect(), p))
		{
			about->isactive = false;
			exitabout->isactive = false;
			for (int i = 0; i < 4; ++i)
			{
				aboutfont[i]->isactive = false;
				items[i]->isactive = false;
			}
			currentIndex = 0;
			return;
		}
		if (PtInRect(&buttons[0]->GetRect(), p))
		{
			Director::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
		if (PtInRect(&buttons[1]->GetRect(), p))
		{
			// 게임 방법 띄우기
			return;
		}
		if (PtInRect(&buttons[2]->GetRect(), p))
		{
			about->isactive = true;
			exitabout->isactive = true;
			for (int i = 0; i < 4; ++i)
			{
				aboutfont[i]->isactive = true;
				aboutfont[i]->SetFont((char*)aboutexamples[i].second.c_str());
				items[i]->isactive = true;
				items[i]->SetTexture(aboutexamples[i].first);
			}
			currentIndex = 0;
			return;
		}
		if (PtInRect(&buttons[3]->GetRect(), p))
		{
			// 랭킹 띄우기
			Director::GetInstance()->ChangeScene(RANKINGSCENE);
			return;
		}
		if (PtInRect(&buttons[4]->GetRect(), p))
		{
			// 크레딧 띄우기
			return;
		}
	}

	if (about->isactive == true)
	{
		if (DXUTWasKeyPressed(VK_LEFT))
		{
			--currentIndex;
			if (currentIndex < 0)
				currentIndex = 0;
		}
		else if (DXUTWasKeyPressed(VK_RIGHT))
		{
			++currentIndex;
			if (currentIndex > maxIndex)
				currentIndex = maxIndex;
		}

		for (int i = 0; i < 4; ++i)
		{
			int index = (currentIndex * 4) + i;
			aboutfont[i]->SetFont((char*)aboutexamples[index].second.c_str());
			items[i]->SetTexture(aboutexamples[index].first);
		}
	}
}

void MenuScene::Exit()
{
	for (int i = 0; i < 5; ++i)
		delete buttons[i];
	delete about;
	delete exitabout;
	for (int i = 0; i < 4; ++i)
	{
		delete items[i];
		delete aboutfont[i];
	}
}
