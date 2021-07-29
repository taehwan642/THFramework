#pragma once

enum class PlayerStates
{
	IDLE,
	RUN,
	ATTACK,
	JUMP,
	JUMPEND,
	DAMAGED,
	DODGE,
	SUPER
};

class IdleState final :
	public GameObjectState
{
public:
	explicit IdleState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] int
		handleInput() override;
};

class RunState final :
	public GameObjectState
{
	int keys[2];

public:
	explicit RunState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] int
		handleInput() override;
};

class AttackState final :
	public GameObjectState
{
public:
	explicit AttackState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] int
		handleInput() override;
};

class JumpState final :
	public GameObjectState
{
public:
	explicit JumpState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] int
		handleInput() override;
};

class JumpEndState final :
	public GameObjectState
{
public:
	explicit JumpEndState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] int
		handleInput() override;
};

class DamagedState final :
	public GameObjectState
{
	float deltatime;
public:
	explicit DamagedState(GameObject* p) : 
		GameObjectState(p), deltatime(0.f)
	{};
	[[nodiscard]] int
		handleInput() override;
};

class DodgeState final :
	public GameObjectState
{
public:
	explicit DodgeState(GameObject* p) :
		GameObjectState(p)
	{};
	[[nodiscard]] int
		handleInput() override;
};

class SuperState final :
	public GameObjectState
{
public:
	explicit SuperState(GameObject* p) :
		GameObjectState(p)
	{};
	[[nodiscard]] int
		handleInput() override;
};