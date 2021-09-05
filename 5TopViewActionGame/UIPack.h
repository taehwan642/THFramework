#pragma once

class Sprite;
class Player;
class Font;

class UIPack
{
public:
	// Pack package
	// ui������
	Player* pl;
	Sprite* playerhp[PLAYERMAXHP];
	Font* score = nullptr;
	// ���� �ð� ����ϴ� ��Ʈ
	Font* lastTime = nullptr;

	float* plastTime = nullptr;

	void Init(Player* p, float* lt);
	void PlayerHPUIUpdate();
	void PlayerScoreUpdate();
	void Update();
	void Delete();
};

