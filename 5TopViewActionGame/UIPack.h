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
	// ui모음집
	Player* pl;
	Sprite* playerhp;
	Font* score = nullptr;
	// 제한 시간 출력하는 폰트
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

	// 패배 폰트
	// 나가기 버튼 -> 메뉴로
	// 재시작 버튼 -> 다시 Stage

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

