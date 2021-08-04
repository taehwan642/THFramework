#include "DXUT.h"
#include "HPUI.h"

HPUI::HPUI(const std::wstring& tag, const std::wstring& bartag) :
	obj(nullptr),
	bar(nullptr),
	MaxHP(0),
	HP(0),
	up(0)
{
	layer = 0;
	SetTexture(tag);
	RenderManager::GetInstance().Sort();
	bar = new AniSprite;
	bar->layer = 1;
	bar->SetTexture(bartag);
	RenderManager::GetInstance().Sort();
}


void HPUI::Update()
{
	
	float result = bar->GetTexture()->info.Width * (static_cast<float>(HP) / static_cast<float>(MaxHP));
	SetRect(&bar->imgRect, 0, 0, result, bar->GetTexture()->info.Height);
}
