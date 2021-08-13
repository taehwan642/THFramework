#pragma once
#include "PlayerLVupUI.h"
#include "GameObject.h"

class Player final :
    public GameObject
{
private:
public:
    PlayerLVupUI* lvupUI;
    bool isDodging;
    explicit Player();
    virtual ~Player();

    void Action() override;

    __forceinline void GetExp(int expValue);

    __forceinline void LevelUp();

    __forceinline void GetStatUp(StatUp statup);

    bool Check_CanGetAttack() override;
};

void Player::GetExp(int expValue)
{
    this->exp += expValue;
    if (this->exp >= level * 5)
    {
        LevelUp();
    }
}

void Player::LevelUp()
{
    this->exp = 0;
    ++level;
    // 공격력, 공격속도, HP최대치 1씩 증가
    ++attackLevel;
    ++attackSpeed;
    ++MaxHP;
    lvupUI->ShowUI();
}