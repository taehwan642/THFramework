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

// ������ Ÿ��, ������ ��� �ִ� Ŭ����, �ش� ����
template<typename T> T* Singleton<T>::instance = nullptr;