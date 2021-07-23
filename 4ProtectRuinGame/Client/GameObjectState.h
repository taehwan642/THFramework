#pragma once

#define CASTVOIDP(obj) reinterpret_cast<void*>(obj)
class GameObject;

class GameObjectState
{
protected:
	GameObject* object;

public:
	explicit GameObjectState(GameObject* obj) : object(obj) {};
	virtual ~GameObjectState() = default;
	[[nodiscard]] virtual void*
		handleInput() PURE;
};

enum class TestState
{
	IDLE,
	RUN
};

class TestIdleState :
	public GameObjectState
{
public:
	explicit TestIdleState(GameObject* obj) : GameObjectState(obj) {};
	[[nodiscard]] virtual void*
		handleInput();
};

class TestRunState :
	public GameObjectState
{
private:
	int keys[2];
public:
	explicit TestRunState(GameObject* obj) : GameObjectState(obj) {};
	[[nodiscard]] virtual void*
		handleInput();
};

class StateManager
{
private:
	std::map<void*, GameObjectState*> stateMap;
	GameObjectState* currentState;
	void* currentKey;

public:
	explicit StateManager() = default;
	__forceinline void
		ChangeState(void* key)
	{
		if (stateMap.find(key) != stateMap.end())
		{
			currentState = stateMap[key];
			currentKey = key;
		}
	};

	__forceinline void
		AddState(void* key, GameObjectState* state)
	{
		if (stateMap.find(key) == stateMap.end())
		{
			stateMap.emplace(key, state);
		}
	};

	void UpdateState()
	{
		void* statekey = currentState->handleInput();
		if (currentKey != statekey)
		{
			ChangeState(statekey);
		}
	};
};

// map으로 key, value key(state enum) value (state pointer -> 자식 포인터)