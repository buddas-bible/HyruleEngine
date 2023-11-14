#include "ZonaiMath.h"
#include "PxPhysicsAPI.h"

#include "FixedJoint.h"

namespace ZonaiPhysics
{

	void FixedJoint::SetObject(ZnObject*, ZnObject*) noexcept
	{

	}

	void FixedJoint::GetObject(ZnObject*&, ZnObject*&) const noexcept
	{

	}

	void FixedJoint::SetLocalPosition(ObjectIndex _index, const Vector3D& _p) noexcept
	{
		using namespace physx;
		PxTransform transform = joint->getLocalPose((PxJointActorIndex::Enum)_index);
		transform.p.x = _p.x;
		transform.p.y = _p.y;
		transform.p.z = _p.z;
		joint->setLocalPose((PxJointActorIndex::Enum)_index, transform);
	}

	Vector3D FixedJoint::GetLocalPosition(ObjectIndex _index) const noexcept
	{
		using namespace physx;
		PxTransform transform = joint->getLocalPose((PxJointActorIndex::Enum)_index);
		return Vector3D(transform.p.x, transform.p.y, transform.p.z);
	}

	void FixedJoint::SetLocalQuaternion(ObjectIndex _index, const Quaternion& _q) noexcept
	{
		using namespace physx;
		PxTransform transform = joint->getLocalPose((PxJointActorIndex::Enum)_index);
		transform.q.w = _q.w;
		transform.q.x = _q.x;
		transform.q.y = _q.y;
		transform.q.z = _q.z;
		joint->setLocalPose((PxJointActorIndex::Enum)_index, transform);
	}

	Quaternion FixedJoint::GetLocalQuaternion(ObjectIndex _index) const noexcept
	{
		using namespace physx;
		PxTransform transform = joint->getLocalPose((PxJointActorIndex::Enum)_index);
		return Quaternion(transform.q.w, transform.q.x, transform.q.y, transform.q.z);
	}

	Vector3D FixedJoint::GetRelativeLinearVelocity() const noexcept
	{
		using namespace physx;
		PxVec3 velo = joint->getRelativeLinearVelocity();
		return Vector3D(velo.x, velo.y, velo.z);
	}

	Vector3D FixedJoint::GetRelativeAngularVelocity() const noexcept
	{
		using namespace physx;
		PxVec3 velo = joint->getRelativeAngularVelocity();
		return Vector3D(velo.x, velo.y, velo.z);
	}

	void FixedJoint::SetBreakForce(float _force, float _torque) noexcept
	{
		joint->setBreakForce(_force, _torque);
	}

	void FixedJoint::GetBreakForce(float& _force, float& _torque) const noexcept
	{
		joint->getBreakForce(_force, _torque);
	}
}