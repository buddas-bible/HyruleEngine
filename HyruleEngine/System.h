#pragma once
namespace Hyrule
{
	template <typename T>
	class System
	{
	protected:
		System() noexcept = default;

	public:
		static T& GetInstance() noexcept
		{
			static T* instance = nullptr;

			if (instance == nullptr)
			{
				instance = new T;
			}

			return *instance;
		}
	};
}