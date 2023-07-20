#include "Collider.h"

#include "Object.h"
#include <string>

#include "ObjectManager.h"

namespace Hyrule
{
	namespace Physics
	{
		Collider::Collider(Object* _obj) noexcept : 
			object(_obj),
			center(), size(0.5f, 0.5f, 0.5f), isTrigger(false),
			inertia(), centerOfMass(), activate(true)
		{}

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
			// 이걸 어떻게 삭제를 시켜야하나...
			// 함수가 호출될 때, 오브젝트 리스트에서 이친구를 지우는건 알겠는데
			// 객체를 삭제시키는 건 어떻게 해야할까...
			// 우선 오브젝트 리스트에서 지워버리고 삭제큐에 넣어놨다가
			// 프레임 막판에 삭제하는 함수를 호출해달라고 팀원에게 말해야하나...
		}

		void Collider::SetWorldTransform(const Matrix4x4& _mat)
		{
			if (object->GetWorldTM() == _mat)
			{
				return;
			}

			// 같지 않다면 노드를 다시 설정해야함.
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
	}
}
