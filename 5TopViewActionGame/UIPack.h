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
	Sprite* playerhp;
	Font* score = nullptr;
	// ���� �ð� ����ϴ� ��Ʈ
	Font* lastTime = nullptr;
	Sprite* hpgauge = nullptr;

	float* plastTime = nullptr;

	void Init(Player* p, float* lt);
	
	void PlayerHPUIUpdate();
	void PlayerScoreUpdate();
	void SceneLastTimeUpdate();
	void PlayerHPGaugeUpdate();
	
	void Update();
	void Delete();
};

