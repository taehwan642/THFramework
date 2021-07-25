#include "DXUT.h"
#include "Octopus.h"

Octopus::Octopus()
{
	CreateAnimation(L"octoidle", 2, 0.1f);
	PlayAnimation(L"octoidle");
	collider->position.x = 300;
}

Octopus::~Octopus()
{
}

void Octopus::Action()
{
	PlayAnimation(L"octoidle");
}
