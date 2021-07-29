#pragma once
#include "GameObject.h"
class Monster :
    public GameObject
{
public:
    Player* player;
    explicit Monster(Player* p) : player(p) {};
    virtual ~Monster();

    void Damaged() override {};
    
    static float monstertimeScale;

    __forceinline static float 
        GetDT() { return DXUTGetElapsedTime() * monstertimeScale; };

    bool PlayAnimationM(const std::wstring& tag);

    void Action() override;
};

