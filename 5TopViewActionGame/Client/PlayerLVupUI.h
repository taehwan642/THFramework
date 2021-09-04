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
	// statupUI 3���� ȭ�鿡 ����, ������ statupUI �� statup�� ��ϵ� ������ ���� �÷��̾��� �ɷ��� ���׷��̵� ��Ų��.
	void Update();
	void ShowUI();
};

