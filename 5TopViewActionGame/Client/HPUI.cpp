#include "DXUT.h"
#include "HPUI.h"

HPUI::HPUI(const std::wstring& tag, const std::wstring& bartag) :
	obj(nullptr),
	bar(nullptr),
	MaxHP(0),
	HP(0),
	up(0)
{
	layer = 1;
	SetTexture(tag);
	bar = new AniSprite;
	bar->SetTexture(bartag);
}


void HPUI::Update()
{
	float result = bar->GetTexture()->info.Width * (static_cast<float>(HP) / static_cast<float>(MaxHP));
	SetRect(&bar->imgRect, 0, 0, result, bar->GetTexture()->info.Height);
}
