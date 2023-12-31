#pragma once

namespace Hyrule
{
	namespace Physics
	{
		template <typename T>
		class Manager
		{
		protected:
			Manager() noexcept = default;

		public:
			static T& GetInstance() noexcept
			{
				static T* instance;

				if (instance == nullptr)
				{
					instance = new T;
				}

				return *instance;
			}
		};
	}
}