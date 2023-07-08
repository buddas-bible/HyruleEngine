#include "Collider.h"

#include "Shape.h"
#include "Object.h"
#include "PHYSICALLYOBJECT_INFO.h"


namespace Hyrule
{
	namespace Physics
	{
		void Collider::SetWorldTransformMatrix(const Matrix4x4& _TM)
		{
			object->SetWorldTM(_TM);
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

		bool Collider::IsColliding()
		{
			return false;
		}
	}
}

//