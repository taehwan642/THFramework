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

    void HpUIUp(int healvalue); // ȸ�� ������ ȸ��
    
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
    // ������ �ʴ� �帧 ���̿� ���ϴ°� �ִٸ�
    // �װ� �����Լ���.
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

// ���� �ڱⰡ ���� Ű waskeypressed �˻�
// Ű ������ �迭�� ����ִ�.
// �ڱⰡ ���� Ű�� Ư�� Ű���ϰ� �����Ǿ��ִٸ�
// �װŸ� �� �˻�.