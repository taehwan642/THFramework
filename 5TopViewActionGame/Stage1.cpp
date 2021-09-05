#include "DXUT.h"
#include "Player.h"
#include "UIPack.h"
#include "Stage1.h"

void Stage1::Init()
{
	// �÷��̾�
	
	p = new Player;
	p->position = { screenwidth / 2, screenheight / 2 };

	uipack = new UIPack;
	uipack->Init(p, &coolTime);
	// UI
	// ��
}

void Stage1::Update()
{
	coolTime -= DXUTGetElapsedTime();
	uipack->Update();
}

void Stage1::Exit()
{
	uipack->Delete();
	delete p;
}
