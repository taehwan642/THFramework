#pragma once
#include "DXUT.h"

#define STC(en) static_cast<int>(en)

class GameObject;

class GameObjectState
{
protected:
	GameObject* object;

public:
	explicit GameObjectState(GameObject* obj) : object(obj) {};
	virtual ~GameObjectState() = default;
	[[nodiscard]] virtual int
		handleInput() PURE;
};

class StateManager
{
private:
	std::map<int, GameObjectState*> stateMap;
	GameObjectState* currentState = nullptr;
	int currentKey = -1;

public:
	explicit StateManager() = default;
	__forceinline void
		ChangeState(int key)
	{
		if (stateMap.find(key) != stateMap.end())
		{
			currentState = stateMap[key];
			currentKey = key;
		}
	};

	__forceinline void
		AddState(int key, GameObjectState* state)
	{
		if (stateMap.find(key) == stateMap.end())
		{
			stateMap.emplace(key, state);
		}
	};

	void UpdateState()
	{
		if (nullptr == currentState)
			return;

		int statekey = currentState->handleInput();
		if (currentKey != statekey)
		{
			ChangeState(statekey);
		}
	};

	__forceinline void 
		DeleteStates()
	{
		for (auto& iter : stateMap)
		{
			delete iter.second;
		}
		stateMap.clear();
	}
};