#include "DXUT.h"
#include "TileMapManager.h"
#include "Monster.h"
float Monster::monstertimeScale = 1.f;

Monster::~Monster()
{
}

void 
Monster::Action()
{
	
}

bool 
Monster::PlayAnimationM(const std::wstring& tag)
{
	return monstertimeScale == 0.f ? false : PlayAnimation(tag);
}
