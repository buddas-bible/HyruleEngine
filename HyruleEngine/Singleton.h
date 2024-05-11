#pragma once
#include <memory>

namespace hyrule
{
	template <typename _Ty>
	class Singleton
	{
	protected:
		Singleton() = default;
		~Singleton() = default;
		Singleton& operator=(const Singleton&) = delete;
		Singleton&& operator=(Singleton&&) noexcept = delete;

	public:
		static std::weak_ptr<_Ty> Instance()
		{
			if (!instance.get())
				instance = std::make_shared<_Ty>();

			return instance;
		}

		static void Release()
		{
			if (instance.get())
				instance.release();
		}

	private:
		static std::shared_ptr<_Ty> instance;
	};

	template <typename _Ty>
	std::shared_ptr<_Ty> Singleton<_Ty>::instance = nullptr;
}