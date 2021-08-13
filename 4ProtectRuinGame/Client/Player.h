#pragma once
#include "GameObject.h"

class Player final :
    public GameObject
{
private:
public:
    bool isDodging;
    explicit Player();
    virtual ~Player();

    void Action() override;

    __forceinline void GetExp(int expValue);

    __forceinline void LevelUp();

    bool Check_CanGetAttack() override;
};

void Player::GetExp(int expValue)
{
    this->exp += expValue;
    if (this->exp >= level * 5)
    {
        ++level;
        LevelUp();
        this->exp = 0;
    }
}

void Player::LevelUp()
{

}