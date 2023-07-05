#include "Collider.h"

#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
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

		// std::vector<Vector3D> Collider::GetPoints()
		// {
		// 
		// }
		// 
		// std::vector<size_t> Collider::GetIndex()
		// {
		// 
		// }
		// 
		// void Collider::CalculateCenterOfMassAndInertiaTensor()
		// {
		// 	
		// }

	}
}

//