#pragma once

enum class PlayerStates
{
	IDLE,
	RUN,
	ATTACK,
	JUMP,
	JUMPEND
};

class Player;

class PlayerState
{
protected:
	Player* player;

public:
	explicit PlayerState(Player* p) : player(p) {};
	[[nodiscard]] virtual PlayerStates 
		handleInput() PURE;
};

class IdleState final :
	public PlayerState
{
public:
	explicit IdleState(Player* p) : PlayerState(p) {};
	[[nodiscard]] PlayerStates
		handleInput() override;
};

class RunState final :
	public PlayerState
{
	int keys[2];

public:
	explicit RunState(Player* p) : PlayerState(p) {};
	[[nodiscard]] PlayerStates
		handleInput() override;
};

class AttackState final :
	public PlayerState
{
public:
	explicit AttackState(Player* p) : PlayerState(p) {};
	[[nodiscard]] PlayerStates
		handleInput() override;
};

class JumpState final :
	public PlayerState
{
public:
	explicit JumpState(Player* p) : PlayerState(p) {};
	[[nodiscard]] PlayerStates
		handleInput() override;
};

class JumpEndState final :
	public PlayerState
{
public:
	explicit JumpEndState(Player* p) : PlayerState(p) {};
	[[nodiscard]] PlayerStates
		handleInput() override;
};