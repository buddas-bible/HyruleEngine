#pragma once
#include "ForceType.h"
#include "ZnRigidBody.h"

#define OVERRIDE override

namespace ZonaiMath
{
	class Vector3D;
}

namespace physx
{
	class PxPhysics;
	class PxRigidDynamic;
	class PxRigidActor;
}


namespace ZonaiPhysics
{
	using namespace ZonaiMath;

	class RigidBody : public ZnRigidBody
	{
	public:
							RigidBody() = delete;
							RigidBody(physx::PxPhysics*&);
		virtual				~RigidBody();

	public:
		virtual void		WakeUp() override;
		virtual bool		IsSleeping() const override;

		virtual DynamicLocks GetDynamicLockFlags() const override;
		virtual void		SetDynamicLockFlag(DynamicLock flag, bool) override;
		virtual void		SetDynamicLockFlags(DynamicLocks flags) override;
		
		virtual void*		GetUserData() const override;
		virtual void		SetUserData(void*) override;

	public:
		// Áú·®
		virtual float		GetMass() const override;
		virtual void		SetMass(float) override;
		virtual float		GetInvMass() const override;

		virtual Vector3D	GetInertiaTensor() const override;
		virtual void		SetInertiaTensor(const Vector3D&) override;

		virtual float		GetLinearDamping() const override;
		virtual void		SetLinearDamping(float) override;

		virtual float		GetAngularDamping() const override;
		virtual void		SetAngularDamping(float) override;
		
	public:
		// ¼Óµµ
		virtual Vector3D	GetLinearVelocity() const override;
		virtual void		SetLinearVelocity(const Vector3D&) override;

		virtual Vector3D	GetAngularVelocity() const override;
		virtual void		SetAngularVelocity(const Vector3D&) override;
		
		virtual float		GetMaxLinearVelocity() const override;
		virtual void		SetMaxLinearVelocity(const float&) override;

		virtual float		GetMaxAngularVelocity() const override;
		virtual void		SetMaxAngularVelocity(const float&) override;

		virtual Vector3D	GetPosition() const override;
		virtual void		SetPosition(const Vector3D&) override;

		virtual Quaternion	GetQuaternion() const override;
		virtual void		SetQuaternion(const Quaternion&) override;

		// Èû
		virtual void		AddForce(const Vector3D&, ForceType) override;
		virtual void		ClearForce() override;
	
		virtual void		AddTorque(const Vector3D&, ForceType) override;
		virtual void		ClearTorque() override;

	public:
		__declspec(property(get = GetLinearDamping, put = SetLinearDamping)) 
			float linerDamping;

		__declspec(property(get = GetAngularDamping, put = SetAngularDamping)) 
			float angularDamping;

		__declspec(property(get = GetLinearVelocity, put = SetLinearVelocity))
			Vector3D linerVelocity;

		__declspec(property(get = GetAngularVelocity, put = SetAngularVelocity)) 
			Vector3D angularVelocity;

		__declspec(property(get = GetMaxLinearVelocity, put = SetMaxLinearVelocity))
			float maxLinearVelocity;

		__declspec(property(get = GetMaxAngularVelocity, put = SetMaxAngularVelocity))
			float maxAngularVelocity;

		__declspec(property(get = GetPosition, put = SetPosition))
			Vector3D position;

		__declspec(property(get = GetQuaternion, put = SetQuaternion))
			Quaternion quaternion;

	private:
		physx::PxRigidDynamic* rigidbody_;
<<<<<<< HEAD
		physx::PxRigidStatic* rigidstatic_;
=======
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
	};
} // namespace ZonaiPhysics

