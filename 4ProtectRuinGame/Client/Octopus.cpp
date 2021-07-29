#include "DXUT.h"
#include "Octopus.h"

Octopus::Octopus(Player* p) :
	Monster(p)
{
	CreateAnimation(L"octoidle", 2, 0.1f);
	CreateAnimation(L"octowalk", 2, 0.1f);
	CreateAnimation(L"octoattack", 2, 0.3f);
	CreateAnimation(L"octohurt", 2, 0.1f);
	PlayAnimationM(L"octoidle");

	stm->AddState(STC(OctopusState::IDLE), new OctopusIdleState(this));
	stm->AddState(STC(OctopusState::ATTACK), new OctopusAttackState(this));
	stm->AddState(STC(OctopusState::WALK), new OctopusWalkState(this));
	stm->AddState(STC(OctopusState::FOLLOW), new OctopusFollowState(this));
	stm->AddState(STC(OctopusState::DAMAGED), new OctopusDamagedState(this));
	stm->ChangeState(STC(OctopusState::IDLE));
	attackSpeed = 1.f;
}

Octopus::~Octopus()
{
}

void Octopus::Action()
{
}
