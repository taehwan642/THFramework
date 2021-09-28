#pragma once

#define TIMECOST 180
// 3�� ����

class Scene
{
protected:
	explicit Scene() = default;

public:
	float coolTime = TIMECOST;

	virtual ~Scene() = default;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Exit() PURE;
};

