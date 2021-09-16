#include "DXUT.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "Button.h"
#include "MainScene.h"

void MainScene::Init()
{
	background = new Sprite;
	background->isUI = true;
	background->SetTexture(L"background.png");
	background->position = { screenwidth / 2, screenheight / 2 };

	Testbutton = new Button;
	Testbutton->isUI = true;
	Testbutton->SetTexture(L"Start.png");
	Testbutton->position = { screenwidth / 2, screenheight / 2 };

	Testbutton->function = []() {
		SceneManager::GetInstance().ChangeScene(L"Stage1");
	};
}

void MainScene::Update()
{
	POINT p;
	Camera& cm = Camera::GetInstance();
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);

	p.x = (-screenwidth / 2 + cm.camPos.x) + p.x;
	p.y = (-screenheight / 2 + cm.camPos.y) + p.y;

	if (PtInRect(&Testbutton->GetRect(), p))
	{
		if (DXUTIsMouseButtonDown(0))
		{
			Testbutton->function();
		}
	}

}

void MainScene::Exit()
{
	delete background;
	delete Testbutton;
}
