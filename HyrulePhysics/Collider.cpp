#include "Collider.h"

#include "Object.h"
#include <string>

namespace Hyrule
{
	namespace Physics
	{
		bool Collider::isActive()
		{
			return this->activate;
		}

		void Collider::OnEnable() noexcept
		{
			this->activate = true;
		}

		void Collider::OnDisable() noexcept
		{
			this->activate = false;
		}

		void Collider::OnDestroy() noexcept
		{
			// 오브젝트 매니저에서 삭제를 요청.
		}

		void Collider::SetWorldTransform(const Matrix4x4& _mat)
		{
			this->object->SetWorldTM(_mat);
		}

		void Collider::SetTrigger(bool _trigger)
		{
			this->isTrigger = _trigger;
		}

		void Collider::SetSize(const Vector3D& _size)
		{
			this->size = _size;
		}

		void Collider::SetCenter(const Vector3D& _center)
		{
			this->center = _center;
		}

		std::wstring Collider::GetObjectName()
		{
			return this->object->GetName();
		}

		//		bool Collider::IsColliding()
		//		{
		//			return this->collided;
		//		}
	}
}
