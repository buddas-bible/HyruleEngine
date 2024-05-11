#pragma once

namespace hyrule
{
	namespace Physics
	{
		template <typename T>
		class Manager
		{
		protected:
			Manager() = default;

		public:
			static T& GetInstance()
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