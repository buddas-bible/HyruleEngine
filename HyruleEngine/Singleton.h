#pragma once
namespace Hyrule
{
	template <typename T>
	class Singleton
	{
	protected:
		Singleton() = default;
		~Singleton() = default;
		Singleton& operator=(const Singleton&) = delete;
		Singleton&& operator=(Singleton&&) noexcept = delete;

	public:
		static T* Instance()
		{
			if (instance)
				instance = new T();

			return instance;
		}

		static void Release()
		{
			if (instance)
				delete instance;

			instance = nullptr;
		}

	private:
		static T* instance;
	};

	template <typename T>
	T* Singleton<T>::instance = nullptr;
}