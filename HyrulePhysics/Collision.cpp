#include "Collision.h"


namespace Hyrule
{
	namespace Physics
	{
		ICollider* Collision::Collider()
		{
			return collider;
		}


		void* Collision::UserData()
		{
			return userData;
		}

		std::wstring Collision::InstanceID()
		{
			return instanceID;
		}

		std::wstring Collision::Tag()
		{
			return tag;
		}

		Vector3D Collision::Impulse()
		{
			return impulse;
		}

		std::vector<Vector3D> Collision::Contacts()
		{
			return contactPoints;
		}

		Vector3D Collision::Contact(size_t _index)
		{
			return contactPoints[_index];
		}

		size_t Collision::ContactCount()
		{
			return contactPoints.size();
		}

		Vector3D Collision::Normal()
		{
			return normal;
		}
	}
}