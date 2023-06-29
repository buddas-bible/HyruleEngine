#pragma once

namespace Hyrule
{
	namespace Physics
	{
		class ICollider
		{
		public:
			ICollider() noexcept = default;
			virtual ~ICollider() noexcept = default;

		public:
			virtual bool GetCollided() abstract;

		};
	}
}