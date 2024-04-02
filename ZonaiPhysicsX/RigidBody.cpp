#include "RigidBody.h"
#include "ZonaiMath.h"
#include "PxPhysicsAPI.h"

namespace ZonaiPhysics
{
<<<<<<< HEAD
	RigidBody::RigidBody()
	{

	}

	RigidBody::RigidBody(physx::PxPhysics*& _factory)
	{
		using namespace physx;
		rigidbody_ = _factory->createRigidDynamic(PxTransform(PxVec3()));
	}

	RigidBody::~RigidBody()
	{
		rigidbody_->release();
	}

	void RigidBody::WakeUp()
	{
=======
	void RigidBody::WakeUp()
	{
		PxFilterFlag

>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
		rigidbody_->wakeUp();
	}

	bool RigidBody::IsSleeping() const
	{
		rigidbody_->isSleeping();
	}

	DynamicLocks RigidBody::GetDynamicLockFlags() const
	{
		return (uint8_t)rigidbody_->getRigidDynamicLockFlags();
	}

	void RigidBody::SetDynamicLockFlag(DynamicLock _flag, bool _value)
	{
		using namespace physx;
		rigidbody_->setRigidDynamicLockFlag((PxRigidDynamicLockFlag::Enum)_flag, _value);
	}

	void RigidBody::SetDynamicLockFlags(DynamicLocks _flags)
	{
		using namespace physx;
		rigidbody_->setRigidDynamicLockFlags((PxRigidDynamicLockFlags)(_flags));
	}

	void* RigidBody::GetUserData() const
	{
		return rigidbody_->userData;
	}

	void RigidBody::SetUserData(void* _userData)
	{
		rigidbody_->userData = _userData;
	}

	float RigidBody::GetMass() const
	{
		return rigidbody_->getMass();
	}

	void RigidBody::SetMass(float _mass)
	{
		rigidbody_->setMass(_mass);
	}

	float RigidBody::GetInvMass() const
	{
		return rigidbody_->getInvMass();
	}

	Vector3D RigidBody::GetInertiaTensor() const
	{
		using namespace physx;
		PxVec3 I = rigidbody_->getMassSpaceInertiaTensor();
		return Vector3D(I.x, I.y, I.z);
	}

	void RigidBody::SetInertiaTensor(const Vector3D& _I)
	{
		using namespace physx;
		rigidbody_->setMassSpaceInertiaTensor(PxVec3(_I.x, _I.y, _I.z));
	}

	float RigidBody::GetLinearDamping() const
	{
		return rigidbody_->getLinearDamping();
	}

	void RigidBody::SetLinearDamping(float _damping)
	{
		rigidbody_->setLinearDamping(_damping);
	}

	float RigidBody::GetAngularDamping() const
	{
		return rigidbody_->getAngularDamping();
	}

	void RigidBody::SetAngularDamping(float _damping)
	{
		rigidbody_->setAngularDamping(_damping);
	}

	Vector3D RigidBody::GetLinearVelocity() const
	{
		using namespace physx;
		PxVec3 v = rigidbody_->getLinearVelocity();
		return Vector3D(v.x, v.y, v.z);
	}

	void RigidBody::SetLinearVelocity(const Vector3D& _velocity)
	{
		using namespace physx;
		rigidbody_->setLinearVelocity(PxVec3(_velocity.x, _velocity.y, _velocity.z));
	}

	Vector3D RigidBody::GetAngularVelocity() const
	{
		using namespace physx;
		PxVec3 v = rigidbody_->getAngularVelocity();
		return Vector3D(v.x, v.y, v.z);
	}

	void RigidBody::SetAngularVelocity(const Vector3D& _velocity)
	{
		using namespace physx;
		rigidbody_->setAngularVelocity(PxVec3(_velocity.x, _velocity.y, _velocity.z));
	}

	float RigidBody::GetMaxLinearVelocity() const
	{
		return rigidbody_->getMaxLinearVelocity();
	}

	void RigidBody::SetMaxLinearVelocity(const float& _maxVelocity)
	{
		rigidbody_->setMaxLinearVelocity(_maxVelocity);
	}

	float RigidBody::GetMaxAngularVelocity() const
	{
		return rigidbody_->getMaxAngularVelocity();
	}

	void RigidBody::SetMaxAngularVelocity(const float& _maxVelocity)
	{
		rigidbody_->setMaxAngularVelocity(_maxVelocity);
	}

	Vector3D RigidBody::GetPosition() const
	{
		auto transform = rigidbody_->getGlobalPose();
		return Vector3D(transform.p.x, transform.p.y, transform.p.z);
	}

	void RigidBody::SetPosition(const Vector3D& _position)
	{
		using namespace physx;
		PxTransform t = rigidbody_->getGlobalPose();
		t.p.x = _position.x;
		t.p.y = _position.y;
		t.p.z = _position.z;
		rigidbody_->setGlobalPose(t);
	}

	Quaternion RigidBody::GetQuaternion() const
	{
		using namespace physx;
		PxTransform t = rigidbody_->getGlobalPose();
		return Quaternion(t.q.w, t.q.x, t.q.y, t.q.z);
	}

	void RigidBody::SetQuaternion(const Quaternion& _quaternion)
	{
		using namespace physx;
		PxTransform t = rigidbody_->getGlobalPose();
		t.q.w = _quaternion.w;
		t.q.x = _quaternion.x;
		t.q.y = _quaternion.y;
		t.q.z = _quaternion.z;
		rigidbody_->setGlobalPose(t);
	}

	void RigidBody::AddForce(const Vector3D& _force, ForceType _type)
	{
		using namespace physx;
		rigidbody_->addForce(PxVec3(_force.x, _force.y, _force.z), (PxForceMode::Enum)_type);
	}

	void RigidBody::ClearForce()
	{
		rigidbody_->clearForce();
	}

	void RigidBody::AddTorque(const Vector3D& _torque, ForceType _type)
	{
		using namespace physx;
		rigidbody_->addForce(PxVec3(_torque.x, _torque.y, _torque.z), (PxForceMode::Enum)_type);
	}

	void RigidBody::ClearTorque()
	{
		rigidbody_->clearTorque();
	}
} // namespace ZonaiPhysics