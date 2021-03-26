#include "DXUT.h"
#include "GameScene.h"
#include "MenuScene.h"

void MenuScene::Init()
{
	start = new Sprite();
	start->SetTexture(L"gamestart.png");
	start->position = { ScreenW / 2, ScreenH / 2 };
	start->scale = { 0.3f,0.3f };
}

void MenuScene::Update()
{
	if (DXUTIsMouseButtonDown(VK_LEFT))
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(DXUTGetHWND(), &p);
		if (PtInRect(&start->GetRect(), p))
		{
			Director::GetInstance()->ChangeScene(GAMESCENE);
			return;
		}
	}
}

void MenuScene::Exit()
{
	delete start;
}
