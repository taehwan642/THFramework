#pragma once
class Scene
{
protected:
	explicit Scene() = default;

public:
	virtual ~Scene() = default;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Exit() PURE;
};

