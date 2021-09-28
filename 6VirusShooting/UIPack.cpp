#include "DXUT.h"
#include "AniSprite.h"
#include "UIPack.h"

void UIPack::Init()
{
	background = new AniSprite;
	background->isUI = true;
	background->CreateAnimation(L"Sprites/map/back", 2, 1.1f);
	background->position = MIDDLE;
	background->PlayAnimation(L"Sprites/map/back");
}

void UIPack::Update()
{
	background->PlayAnimation(L"Sprites/map/back");
}

void UIPack::Delete()
{
	delete background;
}
