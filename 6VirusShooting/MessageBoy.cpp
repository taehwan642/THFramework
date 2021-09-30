#include "DXUT.h"
#include "Font.h"
#include "Sprite.h"
#include "MessageBoy.h"

void MessageBoy::Create()
{
	text = new Font(4, 1, L"Arial");
	text->isUI = true;
	text->layer = 200;

	boy = new Sprite;
	boy->isUI = true;
	boy->SetTexture(L"Sprites/ui/ingame/messagebox.png");
	boy->position = { 1100, 600 };
	pos[0] = { 1100, 600 };

	back = new Sprite;
	back->isUI = true;
	back->SetTexture(L"Sprites/ui/ingame/textui.png");
	back->position = { 900, 500 };
	pos[1] = { 900, 500 };

	text->Adapt(back->position, (Texture*)back->GetTexture(), back->scale, Vec2(20, 20));
	text->SetText("��..");

	startPos = { 1900, 600 };
}

void MessageBoy::SpawnBoy(std::string textmsg)
{
	text->SetText((char*)textmsg.c_str());
	back->position = startPos;
	boy->position = startPos;
	text->Adapt(back->position, (Texture*)back->GetTexture(), back->scale, Vec2(20, 20));
	isGoing = true;
	goBack = false;

	// �ְ� ȭ���࿡ ���ͼ�
	// ���ϰ�
	// ���ʵڿ�
	// ȭ������� ������.
}

void MessageBoy::Update()
{
	if (false == isGoing)
		return;

	// 1. �ְ� ���Ϳ�
	// 2. �����ִٰ� �ٽ� ����

	// Lerp�� ���Ϳ�. �����鼭 �ʵ� ������.
	// ���� �̻� �������� �ٽ� ���� ���ѿ�.

	if (false == goBack)
	{
		tick += Time::dt;
		D3DXVec2Lerp(&boy->position, &boy->position, &pos[0], Time::dt);
		D3DXVec2Lerp(&back->position, &back->position, &pos[1], Time::dt);
		if (fabs(boy->position.x - pos[0].x) < 5.f && tick > 1.f)
		{
			goBack = true;
		}
	}
	else
	{
		D3DXVec2Lerp(&boy->position, &boy->position, &startPos, Time::dt);
		D3DXVec2Lerp(&back->position, &back->position, &startPos, Time::dt);
		if (fabs(boy->position.x - endPos.x) < 5.f)
		{
			isGoing = false;
		}
	}

	text->Adapt(back->position, (Texture*)back->GetTexture(), back->scale, Vec2(20, 20));
}

void MessageBoy::Delete()
{
	delete back;
	delete boy;
	delete text;
}
