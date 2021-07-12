#pragma once

enum class PlayerStates
{
	IDLE,
	RUN,
	ATTACK
};

class PlayerState
{
public:
	[[nodiscard]] virtual PlayerStates 
		handleInput() PURE;
};

class IdleState final :
	public PlayerState
{
public:
	[[nodiscard]] PlayerStates 
		handleInput() override
	{
		if (DXUTWasKeyPressed('W') 
			|| DXUTWasKeyPressed('A') 
			|| DXUTWasKeyPressed('S') 
			|| DXUTWasKeyPressed('D'))
		{
			return PlayerStates::RUN;
		}

		if (DXUTWasKeyPressed(VK_SPACE))
			return PlayerStates::ATTACK;

		return PlayerStates::IDLE;
	}
};

class RunState final :
	public PlayerState
{
	int keys[4];

public:
	[[nodiscard]] PlayerStates 
		handleInput() override
	{
		if (DXUTIsKeyDown('W')) keys[0] = 1;
		else keys[0] = 0;
		
		if (DXUTIsKeyDown('A')) keys[1] = 1;
		else keys[1] = 0;

		if (DXUTIsKeyDown('S')) keys[2] = 1;
		else keys[2] = 0;

		if (DXUTIsKeyDown('D')) keys[3] = 1;
		else keys[3] = 0;

		int result = keys[0] + keys[1] + keys[2] + keys[3];

		if(result == 0)
			return PlayerStates::IDLE;

		if (DXUTWasKeyPressed(VK_SPACE))
			return PlayerStates::ATTACK;
		
		return PlayerStates::RUN;
	}
};

class AttackState final :
	public PlayerState
{
public:
	[[nodiscard]] PlayerStates 
		handleInput() override
	{
		// ¸Ó ÇÏ°í
		return PlayerStates::IDLE;
	}
};