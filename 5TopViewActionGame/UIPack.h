#pragma once

class Sprite;
class Player;
class Font;
class AniSprite;
class Button;

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

	Sprite* aim = nullptr;

	AniSprite* sea = nullptr;

	Sprite* attackgaugeOutline = nullptr;
	AniSprite* attackgaugeBar = nullptr;

	Sprite* scoreboard = nullptr;
	Font* scorefont = nullptr;
	Button* scoreButton = nullptr;
	bool isButtonOn = false;

	// �й� ��Ʈ
	// ������ ��ư -> �޴���
	// ����� ��ư -> �ٽ� Stage

	float* plastTime = nullptr;

	void Init(Player* p, float* lt);
	
	void ScoreActive(bool b);
	void DieActive(bool b);

	void PlayerHPUIUpdate();
	void PlayerScoreUpdate();
	void SceneLastTimeUpdate();
	void PlayerHPGaugeUpdate();
	void AttackGaugeBarUpdate();
	void ScoreBoardUpdate();


	void Update();
	void Delete();
};

