#include "Object.h"

#include "HyruleMath.h"
#include "Transform.h"
#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		Object::Object(const std::wstring& _name) noexcept
			: name(_name), transform(),
			rigidbody(), colliders()
		{

		}

		Matrix4x4 Object::GetWorldTM()
		{
			return transform->GetWorldTransform();
		}

		Matrix3x3 Object::GetInertiaTensor(float _mess)
		{
			if (colliders.size())
			{
				// 아직은 하나만 할거임...
				return colliders[0]->GetInertiaTensor(_mess);
			}

			return Matrix3x3();
		}

		Vector3D Object::GetCenterOfMess()
		{
			if (colliders.size())
			{
				return colliders[0]->GetCenterOfMess();
			}

			return Vector3D();
		}

	}
}