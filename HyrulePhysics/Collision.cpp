#include "Collision.h"


namespace Hyrule
{
	namespace Physics
	{
		ICollider* Collision::Collider() noexcept
		{
			return collider;
		}


		void* Collision::UserData() noexcept
		{
			return userData;
		}

		std::wstring Collision::InstanceID() noexcept
		{
			return instanceID;
		}

		std::wstring Collision::Tag() noexcept
		{
			return tag;
		}

		Vector3D Collision::Impulse() noexcept
		{
			return impulse;
		}

		std::vector<Vector3D> Collision::Contacts() noexcept
		{
			return contactPoints;
		}

		Vector3D Collision::Contact(size_t _index) noexcept
		{
			return contactPoints[_index];
		}

		size_t Collision::ContactCount() noexcept
		{
			return contactPoints.size();
		}

		Vector3D Collision::Normal() noexcept
		{
			return normal;
		}
	}
}