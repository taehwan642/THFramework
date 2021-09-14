#include "DXUT.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "MainScene.h"

void MainScene::Init()
{
	background = new Sprite;
	background->isUI = true;
	background->SetTexture(L"background.png");
	background->position = { screenwidth / 2, screenheight / 2 };
}

void MainScene::Update()
{
	if (DXUTWasKeyPressed('0'))
		SceneManager::GetInstance().ChangeScene(L"Stage1");
}

void MainScene::Exit()
{
	delete background;
}
