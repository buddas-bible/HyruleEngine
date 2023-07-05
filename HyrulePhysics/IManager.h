#pragma once

// namespace Hyrule
// {
// 	namespace Physics
// 	{
// 		template <typename T>
// 		class IManager
// 		{
// 		protected:
// 			IManager() noexcept = default;
// 
// 		public:
// 			static T& GetInstance() noexcept
// 			{
// 				static T* instance;
// 
// 				if (instance == nullptr)
// 				{
// 					instance = new T;
// 				}
// 
// 				return *instance;
// 			}
// 		};
// 	}
// }