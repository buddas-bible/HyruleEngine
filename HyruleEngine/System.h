#pragma once
namespace Hyrule
{
	template <typename T>
	class System
	{
	protected:
		System() noexcept = default;
		~System() noexcept = default;
		System& operator=(const System&) noexcept = delete;
		System& operator=(System&&) noexcept = delete;

	public:
		static T& GetInstance() noexcept
		{
			static T instance;

// 			if (instance == nullptr)
// 			{
// 				instance = new T;
// 			}

			return instance;
		}
	};
}