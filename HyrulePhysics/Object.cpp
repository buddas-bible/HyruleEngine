#include "Object.h"

#include "HyruleMath.h"
#include "Transform.h"

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
	}
}