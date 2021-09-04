#pragma once
#include "Monster.h"
#include "Octopus.h"
#include "Singleton.h"

enum class MonsterTag
{
    OCTOPUS,
    BOSS
};

class MonsterManager final :
    public Singleton<MonsterManager>
{
public:
    Player* player;
    std::vector<Monster*> monsters;
    __forceinline void 
        CreateMonster()
    {
        for (int i = 0; i < 30; ++i)
        {
            Monster* m = nullptr;
            monsters.emplace_back(m);
        }
    }
    
    __forceinline void 
        SpawnMonster(MonsterTag tag, const Vec2& position, int difficulty)
    {
        for (int i = 0; i < std::size(monsters); ++i)
        {
            if (monsters[i] == nullptr)
            {
                switch (tag)
                {
                case MonsterTag::OCTOPUS:
                    monsters[i] = new Octopus(player);
                    break;
                case MonsterTag::BOSS:
                    monsters[i] = new Boss(player);
                    break;
                default:
                    break;
                }
                monsters[i]->isactive = false;
            }

            // 타입 체크 부분
            Monster* mp = nullptr;
            switch (tag)
            {
            case MonsterTag::OCTOPUS:
                mp = dynamic_cast<Octopus*>(monsters[i]);
                break;
            case MonsterTag::BOSS:
                mp = dynamic_cast<Boss*>(monsters[i]);
                break;
            default:
                break;
            }


            if (nullptr != mp &&
                monsters[i]->isactive == false)
            {
                switch (tag)
                {
                case MonsterTag::OCTOPUS:
                    monsters[i]->PlayAnimation(L"octoidle");
                    monsters[i]->MaxHP = 5 * difficulty;
                    monsters[i]->HP = monsters[i]->MaxHP;
                    break;
                case MonsterTag::BOSS:
                    monsters[i]->PlayAnimation(L"flyidle");
                    monsters[i]->MaxHP = 10 * difficulty;
                    monsters[i]->HP = monsters[i]->MaxHP;
                    break;
                default:
                    break;
                }
                monsters[i]->SetPosition(position);
                monsters[i]->isactive = true;
                monsters[i]->collider->isactive = true;
                return;
            }
        }
    }

    __forceinline void 
        DeleteMonster()
    {
        for (int i = 0; i < std::size(monsters); ++i)
        {
            delete monsters[i];
        }
    }
};

