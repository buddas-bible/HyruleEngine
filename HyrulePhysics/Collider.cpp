#include "Collider.h"

#include "Object.h"
void Hyrule::Physics::Collider::SetWorldTransformMatrix(const Matrix4x4& _mat)
{
	this->object->SetWorldTM(_mat);
}
