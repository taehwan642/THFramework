#include "DXUT.h"
#include "Sprite.h"
#include "Button.h"
#include "SceneManager.h"
#include "Font.h"
#include "FailScene.h"

void FailScene::Init()
{
	back = new Sprite;
	back->isUI = true;
	back->position = { screenwidth / 2, screenheight / 2 };
	back->SetTexture(L"ScoreBoard.png");
	
	restart = new Button;
	restart->function = []() 
	{
		SceneManager::GetInstance().ChangeScene(L"Stage1");
	};
	restart->layer = 1;
	restart->isUI = true;
	restart->position = { screenwidth / 2 - 300, screenheight / 2 + 300 };
	restart->SetTexture(L"Restart.png");

	exit = new Button;
	exit->layer = 1;
	exit->isUI = true;
	exit->position = { screenwidth / 2 + 300, screenheight / 2 + 300 };
	exit->function = []()
	{
		SceneManager::GetInstance().ChangeScene(L"Main");
	};
	exit->SetTexture(L"Exit.png");
}

void FailScene::Update()
{
	if (DXUTIsMouseButtonDown(0))
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(DXUTGetHWND(), &p);
		if (PtInRect(&restart->GetRect(), p))
		{
			restart->function();
			return;
		}
		if (PtInRect(&exit->GetRect(), p))
		{
			exit->function();
			return;
		}
	}
}

void FailScene::Exit()
{
	delete back;
	delete exit;
	delete restart;
}
