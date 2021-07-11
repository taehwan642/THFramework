#pragma once
template<typename T>
class Singleton
{
private:
	static T* instance;

protected:
	explicit Singleton() = default;
	Singleton(const Singleton&) = delete;
	void operator=(const Singleton&) = delete;

public:
	[[nodiscard]] static __forceinline T& GetInstance()
	{
		if (instance == nullptr)
			instance = new T;
		return *instance;
	}

	static __forceinline void DeleteInstance()
	{
		if (instance != nullptr)
			delete instance;
	}
};

// 변수의 타입, 변수를 담고 있는 클래스, 해당 변수
template<typename T> T* Singleton<T>::instance = nullptr;