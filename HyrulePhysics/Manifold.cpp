#include "Manifold.h"


namespace Hyrule
{
	Manifold::Manifold(const Collider*& _A, const Collider*& _B) noexcept
		: A(_A), B(_B), 
		normal{}, tangent{}, depth{}, 
		// contactPoints{},
		contactNormal{}
	{
		
	}

	Vector3D Manifold::GetNormal() const noexcept
	{
		return this->normal;
	}

	void Manifold::SetNormal(const Vector3D& _normal) noexcept
	{
		this->normal = _normal;
	}

	Vector3D Manifold::GetTangent() const noexcept
	{
		return this->tangent;
	}

	void Manifold::SetTangent(const Vector3D& _tangent) noexcept
	{
		this->tangent = _tangent;
	}

	Vector3D Manifold::GetContactNormal() const noexcept
	{
		return this->contactNormal;
	}

	void Manifold::SetContactNormal(const Vector3D& _contactNormal) noexcept
	{
		this->contactNormal = _contactNormal;
	}

	float Manifold::GetDepth() const noexcept
	{
		return this->depth;
	}

	void Manifold::SetDepth(float _depth) noexcept
	{
		this->depth = _depth;
	}
}