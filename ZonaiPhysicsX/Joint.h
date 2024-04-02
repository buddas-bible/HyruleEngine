#pragma once
#include "ZnJoint.h"

namespace ZonaiPhysics
{
	class ZnObject;

<<<<<<< HEAD
	enum ObjectIndex
	{
		OBJECT0,
		OBJECT1,
	};

=======
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
	class Joint : public ZnJoint
	{
	public:
						Joint() = default;
		virtual			~Joint();

	public:
<<<<<<< HEAD
		virtual void		SetObject(ZnObject*, ZnObject*) = 0;
		virtual void		GetObject(ZnObject*&, ZnObject*&) const = 0;

		virtual void		SetLocalPosition(ObjectIndex, const Vector3D&) = 0;
		virtual Vector3D	GetLocalPosition(ObjectIndex) const = 0;

		virtual void		SetLocalQuaternion(ObjectIndex, const Quaternion&) = 0;
		virtual Quaternion	GetLocalQuaternion(ObjectIndex) const = 0;

		virtual Vector3D	GetRelativeLinearVelocity() const = 0;
		virtual Vector3D	GetRelativeAngularVelocity() const = 0;

		virtual void		SetBreakForce(float _force, float _torque) = 0;
		virtual void		GetBreakForce(float& _force, float& _torque) const = 0;
=======
		virtual void		SetObject(ZnObject*, ZnObject*) override;
		virtual void		GetObject(ZnObject*&, ZnObject*&) const override;

		virtual void		SetLocalPosition(const Vector3D&) override;
		virtual Vector3D	GetLocalPosition() const override;

		virtual void		SetLocalQuaternion(const Quaternion&) override;
		virtual Quaternion	GetLocalQuaternion() const override;

		virtual Vector3D	GetRelativeLinearVelocity() const override;
		virtual Vector3D	GetRelativeAngularVelocity() const override;

		virtual void		SetBreakForce(float _force, float _torque) override;
		virtual void		GetBreakForce(float& _force, float& _torque) const override;
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
	};
} // namespace ZonaiPhysics

