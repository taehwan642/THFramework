#pragma once
class AniSprite;
class Sprite;
class Font;
class Player;

class UIPack
{
public:
	Player* player;

	AniSprite* background;
	Font* buffFont[2];

	Sprite* weaponSprite[4];

	void Init();
	void Update();
	void Delete();
};

