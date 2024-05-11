#pragma once
#include "HComponent.h"
#include "HyruleMath.h"

#include <vector>

namespace hyrule
{
	namespace Physics
	{
		class ICollider;
	}

	class HEntity;
	struct Vector3D;

	class HCollider : public HComponent
	{
	public:
		HCollider() = delete;
		HCollider(HEntity*);
		~HCollider() override = default;
	
	public:
		Vector3D center;
		Vector3D size;

	public:
		virtual void SetTrigger(bool) abstract;
		virtual void SetSize(const Vector3D&) abstract;
		virtual void SetCenter(const Vector3D&) abstract;
		virtual bool isCollision() abstract;

	public:
		virtual void PrePhysicsUpdate() abstract;
		virtual void PhysicsUpdate() abstract;
		virtual void LatePhysicsUpdate() abstract;
		virtual void Update() abstract;

		virtual void OnEnable() abstract;
		virtual void OnDisable() abstract;
		virtual void OnDestroy() abstract;
	};
}