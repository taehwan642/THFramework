#pragma once

class Sprite;
class Player;
class Font;

class UIPack
{
public:
	// Pack package
	// ui모음집
	Player* pl;
	Sprite* playerhp[PLAYERMAXHP];
	Font* score = nullptr;
	// 제한 시간 출력하는 폰트
	Font* lastTime = nullptr;

	float* plastTime = nullptr;

	void Init(Player* p, float* lt);
	void PlayerHPUIUpdate();
	void PlayerScoreUpdate();
	void Update();
	void Delete();
};

