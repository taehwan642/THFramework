#include "DXUT.h"
#include "MenuScene.h"

void MenuScene::Init()
{
	sp = new Sprite;
	sp->position = { 256,256 };
	sp->SetTexture(L"1.png");
}

void MenuScene::Update()
{
}

void MenuScene::Exit()
{
	delete sp;
}
