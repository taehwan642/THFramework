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

class StateManager
{
private:
	std::map<void*, GameObjectState*> stateMap;
	GameObjectState* currentState = nullptr;
	void* currentKey = nullptr;

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
		if (nullptr == currentState)
			return;

		void* statekey = currentState->handleInput();
		if (currentKey != statekey)
		{
			ChangeState(statekey);
		}
	};
};