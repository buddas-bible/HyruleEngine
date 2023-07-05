#include "MeshCollider.h"

#include "ICollider.h"

namespace Hyrule
{

	MeshCollider::MeshCollider(GameObject* _gameObject) noexcept : 
		Collider(_gameObject)
	{

	}

	MeshCollider::~MeshCollider() noexcept
	{

	}

	void MeshCollider::SetTrigger(bool)
	{

	}

	void MeshCollider::SetSize(const Vector3D&)
	{

	}

	void MeshCollider::SetCenter(const Vector3D&)
	{

	}

	bool MeshCollider::IsColliding()
	{
		return collider->IsColliding();
	}

}
