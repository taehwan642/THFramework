#include "DXUT.h"
#include "Octopus.h"

Octopus::Octopus(Player* p) :
	Monster(p)
{
	CreateAnimation(L"octoidle", 2, 0.1f);
	CreateAnimation(L"octowalk", 2, 0.1f);
	CreateAnimation(L"octoattack", 2, 0.3f);
	PlayAnimation(L"octoidle");

	stm->AddState(CASTVOIDP(OctopusState::IDLE), new OctopusIdleState(this));
	stm->AddState(CASTVOIDP(OctopusState::ATTACK), new OctopusAttackState(this));
	stm->AddState(CASTVOIDP(OctopusState::WALK), new OctopusWalkState(this));
	stm->AddState(CASTVOIDP(OctopusState::FOLLOW), new OctopusFollowState(this));
	stm->ChangeState(CASTVOIDP(OctopusState::IDLE));
	attackSpeed = 5.f;
}

Octopus::~Octopus()
{
}

void Octopus::Action()
{
}
