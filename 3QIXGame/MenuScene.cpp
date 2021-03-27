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
}

void MenuScene::Update()
{
	if (DXUTIsMouseButtonDown(VK_LEFT))
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(DXUTGetHWND(), &p);
		if (PtInRect(&buttons[0]->GetRect(), p))
		{
			Director::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
		if (PtInRect(&buttons[1]->GetRect(), p))
		{
			// °ÔÀÓ ¹æ¹ý ¶ç¿ì±â
			return;
		}
		if (PtInRect(&buttons[2]->GetRect(), p))
		{
			// °ÔÀÓ ¼Ò°³ ¶ç¿ì±â
			return;
		}
		if (PtInRect(&buttons[3]->GetRect(), p))
		{
			// ·©Å· ¶ç¿ì±â
			Director::GetInstance()->ChangeScene(RANKINGSCENE);
			return;
		}
		if (PtInRect(&buttons[4]->GetRect(), p))
		{
			// Å©·¹µ÷ ¶ç¿ì±â
			return;
		}
	}
}

void MenuScene::Exit()
{
	for (int i = 0; i < 5; ++i)
		delete buttons[i];
}
