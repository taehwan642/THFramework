#pragma once
#include "GameObject.h"

struct SkillKey;
class Player :
    public GameObject
{
public:
    std::vector<SkillKey*> keys;

    float attackupTick = 0.f;
    const int upAttack = 0;

    int score = 0;
    int hpuigauge = 0;

    Player();
    virtual ~Player() {};

    void HpUIUp(int healvalue); // 회복 게이지 회복
    
    void CollideItem();
    void CheckAttackUp();
    void Move();

    void CheckSkillKey();

    void Action() override;
};










struct SkillKey
{
    Player* p;
    std::vector<char> sk;
    bool CheckSkill();
    // 변하지 않는 흐름 사이에 변하는게 있다면
    // 그걸 가상함수로.
    virtual void DoSomething() PURE;
};

struct HealKey : public SkillKey
{
    HealKey(Player* p) { this->p = p; sk.push_back('Z'); }
    void DoSomething() override;
};

struct WeakAttackKey : public SkillKey
{
    WeakAttackKey(Player* p) { this->p = p; 
    sk.push_back('J'); 
    sk.push_back('K');
    sk.push_back('L');
    }
    void DoSomething() override;
};

// 지금 자기가 누른 키 waskeypressed 검사
// 키 조합이 배열에 들어있다.
// 자기가 누른 키가 특정 키패턴과 연관되어있다면
// 그거를 쭉 검사.