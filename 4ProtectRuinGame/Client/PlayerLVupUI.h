#pragma once
#include "Sprite.h"

enum class StatUp
{
	HPUP,
	ATTACKSPEEDUP,
	SPEEDUP,
	ATTACKUP
};

struct StatUpUI :
	public Sprite
{
	StatUp statup;
	void Update() override {};
};

class PlayerLVupUI
{
public:
	PlayerLVupUI();
	StatUpUI* statupUI[3];
	// statupUI 3개를 화면에 띄우고, 선택한 statupUI 속 statup에 기록된 정보를 토대로 플레이어의 능력을 업그레이드 시킨다.
	void Update();
	void ShowUI();
};

