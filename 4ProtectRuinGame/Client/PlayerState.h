#pragma once

enum class PlayerStates
{
	IDLE,
	RUN,
	ATTACK,
	JUMP,
	JUMPEND
};

class IdleState final :
	public GameObjectState
{
public:
	explicit IdleState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] void*
		handleInput() override;
};

class RunState final :
	public GameObjectState
{
	int keys[2];

public:
	explicit RunState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] void*
		handleInput() override;
};

class AttackState final :
	public GameObjectState
{
public:
	explicit AttackState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] void*
		handleInput() override;
};

class JumpState final :
	public GameObjectState
{
public:
	explicit JumpState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] void*
		handleInput() override;
};

class JumpEndState final :
	public GameObjectState
{
public:
	explicit JumpEndState(GameObject* p) : GameObjectState(p) {};
	[[nodiscard]] void*
		handleInput() override;
};