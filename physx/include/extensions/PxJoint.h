// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2023 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef PX_JOINT_H
#define PX_JOINT_H
/** \addtogroup extensions
  @{
*/

#include "foundation/PxTransform.h"
#include "PxRigidActor.h"
#include "PxConstraint.h"
#include "common/PxBase.h"

#if !PX_DOXYGEN
namespace physx
{
#endif

class PxRigidActor;
class PxScene;
class PxPhysics;
class PxConstraint;

/**
\brief an enumeration of PhysX' built-in joint types

@see PxJoint
*/
struct PxJointConcreteType
{
	enum Enum
	{
		eSPHERICAL = PxConcreteType::eFIRST_PHYSX_EXTENSION,
		eREVOLUTE,
		ePRISMATIC,
		eFIXED,
		eDISTANCE,
		eD6,
		eCONTACT,
		eGEAR,
		eRACK_AND_PINION,
		eLast
	};
};

PX_DEFINE_TYPEINFO(PxJoint,					PxConcreteType::eUNDEFINED)
PX_DEFINE_TYPEINFO(PxRackAndPinionJoint,	PxJointConcreteType::eRACK_AND_PINION)
PX_DEFINE_TYPEINFO(PxGearJoint,				PxJointConcreteType::eGEAR)
PX_DEFINE_TYPEINFO(PxD6Joint,				PxJointConcreteType::eD6)
PX_DEFINE_TYPEINFO(PxDistanceJoint,			PxJointConcreteType::eDISTANCE)
PX_DEFINE_TYPEINFO(PxContactJoint,			PxJointConcreteType::eCONTACT)
PX_DEFINE_TYPEINFO(PxFixedJoint,			PxJointConcreteType::eFIXED)
PX_DEFINE_TYPEINFO(PxPrismaticJoint,		PxJointConcreteType::ePRISMATIC)
PX_DEFINE_TYPEINFO(PxRevoluteJoint,			PxJointConcreteType::eREVOLUTE)
PX_DEFINE_TYPEINFO(PxSphericalJoint,		PxJointConcreteType::eSPHERICAL)


/**
\brief an enumeration for specifying one or other of the actors referenced by a joint

@see PxJoint
*/

struct PxJointActorIndex
{
	enum Enum
	{
		eACTOR0,
		eACTOR1,
		COUNT
	};
};

/** 
\brief a base interface providing common functionality for PhysX joints
*/

class PxJoint : public PxBase
{
public:

	/**
	\brief �� ����Ʈ�� ���͸� �����մϴ�.

	���ʹ� ���� �������� ��Ÿ���� ���� NULL�� �� �ֽ��ϴ�. ���� �� �ִ� �ϳ��� NULL�� �� �ֽ��ϴ�.

	\param[in] actor0 ù ��° ����.
	\param[in] actor1 �� ��° ����

	@see getActors()
	*/
	virtual void				setActors(PxRigidActor* actor0, PxRigidActor* actor1)	= 0;

	/**
	\brief �� ����Ʈ�� ���͸� �����ɴϴ�.

	\param[out] actor0 ù ��° ����.
	\param[out] actor1 �� ��° ����

	@see setActors()
	*/
	virtual void				getActors(PxRigidActor*& actor0, PxRigidActor*& actor1)	const	= 0;

	/**
	\brief ������ ����Ʈ ���� ��� �����մϴ�.

	�̰��� ����Ʈ �������� ���Ϳ� ��������� ��ġ�ϴ� ������� �����Դϴ�.

	\param[in] actor ù ��° ���ʹ� 0, �� ��° ���ʹ� 1�Դϴ�.
	\param[in] localPose �� ����Ʈ�� ���Ϳ� ���� ���� �����Դϴ�.

	@see getLocalPose()
	*/
	virtual void				setLocalPose(PxJointActorIndex::Enum actor, const PxTransform& localPose) = 0;

	/**
	\brief ������ ����Ʈ ���� ��� ����ϴ�.

	\param[in] actor ù ��° ���ʹ� 0, �� ��° ���ʹ� 1�Դϴ�.

	����Ʈ�� �� ���� ��� ��ȯ�մϴ�.

	@see setLocalPose()
	*/
	virtual PxTransform			getLocalPose(PxJointActorIndex::Enum actor) const = 0;

	/**
	\brief �� ����Ʈ�� ������� ��� ����ϴ�.

	�� �Լ��� actor1�� ����Ʈ �������� ��� actor0�� ��������� ��ȯ�մϴ�.

	@see setLocalPose()
	*/
	virtual PxTransform			getRelativeTransform()	const	= 0;

	/**
	\brief ����Ʈ�� ������� ���� �ӵ��� ����ϴ�.

	�� �Լ��� actor0�� ���� ����Ʈ �������� ������ ������� actor1�� ���� ����Ʈ �������� ���� �ӵ��� ��ȯ�մϴ�.
	�� ���� actor0�� ���� ����Ʈ ������ ������ ��ȯ�˴ϴ�.
	*/
	virtual PxVec3				getRelativeLinearVelocity()	const	= 0;

	/**
	\brief ����Ʈ�� ������� �� �ӵ��� ����ϴ�.

	�� �Լ��� actor0�� ���� ����Ʈ ������ ������ ��ȯ�� ���� ����Ͽ� actor1�� �� �ӵ��� actor0�� ��������� ��ȯ�մϴ�.
	*/
	virtual PxVec3				getRelativeAngularVelocity()	const	= 0;

	/**
	\brief �� ����Ʈ�� �Ĵ� ���� �����մϴ�.

	����Ʈ�� �������� ���� ���̳� ��ũ�� ������ ������ ũ�� ����Ʈ�� �ĴܵǸ�,
	�� �������� �� ���͸� �������� ������ PxConstraintFlag::eBROKEN �÷��װ� �����˴ϴ�.
	���� ��ũ�� ù ��° ������ ����Ʈ �����ӿ��� �����˴ϴ�.

	\param[in] force �ĴܵǱ� ���� ����Ʈ�� ���� �� �ִ� �ִ� ��
	\param[in] torque �ĴܵǱ� ���� ����Ʈ�� ���� �� �ִ� �ִ� ��ũ
	*/
	virtual void				setBreakForce(PxReal force, PxReal torque)	= 0;

	/**
	\brief �� ������ �Ĵ� ���� �����ɴϴ�.

	\param[out] force �Ĵ��ϱ� ���� ������ ������ �� �ִ� �ִ� ��
	\param[out] torque �Ĵ��ϱ� ���� ������ ������ �� �ִ� �ִ� ��ũ

	@see setBreakForce()
	*/
	virtual void				getBreakForce(PxReal& force, PxReal& torque)	const	= 0;

	/**
	\brief �� ������ ���� ���� ���� �÷��׸� �����մϴ�.

	\param[in] flags ���� ���� �÷���

	@see PxConstraintFlag
	*/
	virtual void				setConstraintFlags(PxConstraintFlags flags)	= 0;

	/**
	\brief �� ������ ���� ���� ���� �÷��׸� ������ ������ �����մϴ�.

	\param[in] flag ���� ���� �÷���
	\param[in] value �÷��׸� ������ ��

	@see PxConstraintFlag
	*/
	virtual void				setConstraintFlag(PxConstraintFlag::Enum flag, bool value)	= 0;

	/**
	\brief get the constraint flags for this joint. 
	
	\return the constraint flags

	@see PxConstraintFlag
	*/
	virtual PxConstraintFlags	getConstraintFlags()	const	= 0;
	
	/**
	\brief actor0�� ������ �������� �����մϴ�.

	\param[in] invMassScale �� ������ �ذ��ϱ� ���� actor 0�� �������� ������ ������

	@see getInvMassScale0
	*/
	virtual void				setInvMassScale0(PxReal invMassScale)	= 0;

	/**
	\brief actor0�� ������ �������� �����ɴϴ�.

	\return actor0�� ������ ������

	@see setInvMassScale0
	*/
	virtual PxReal				getInvMassScale0()	const	= 0;

	/**
	\brief set the inverse inertia scale for actor0.

	\param[in] invInertiaScale the scale to apply to the inverse inertia of actor0 for resolving this constraint

	@see getInvMassScale0
	*/
	virtual void				setInvInertiaScale0(PxReal invInertiaScale)	= 0;

	/**
	\brief get the inverse inertia scale for actor0.

	\return inverse inertia scale for actor0

	@see setInvInertiaScale0
	*/
	virtual PxReal				getInvInertiaScale0()	const	= 0;

	/**
	\brief set the inverse mass scale for actor1.

	\param[in] invMassScale the scale to apply to the inverse mass of actor 1 for resolving this constraint

	@see getInvMassScale1
	*/
	virtual void				setInvMassScale1(PxReal invMassScale)	= 0;

	/**
	\brief get the inverse mass scale for actor1.

	\return inverse mass scale for actor1

	@see setInvMassScale1
	*/
	virtual PxReal				getInvMassScale1()	const	= 0;

	/**
	\brief set the inverse inertia scale for actor1.

	\param[in] invInertiaScale the scale to apply to the inverse inertia of actor1 for resolving this constraint

	@see getInvInertiaScale1
	*/
	virtual void				setInvInertiaScale1(PxReal invInertiaScale)	= 0;

	/**
	\brief get the inverse inertia scale for actor1.

	\return inverse inertia scale for actor1

	@see setInvInertiaScale1
	*/
	virtual PxReal				getInvInertiaScale1()	const	= 0;

	/**
	\brief Retrieves the PxConstraint corresponding to this joint.
	
	This can be used to determine, among other things, the force applied at the joint.

	\return the constraint
	*/
	virtual PxConstraint*		getConstraint()	const	= 0;

	/**
	\brief getName()�� �˻��� �� �ִ� ��ü�� �̸� ���ڿ��� �����մϴ�.

	�̰��� �������̸� SDK������ ������ �ʽ��ϴ�.
	�� ���ڿ��� SDK�� ���� ������� ������ �����͸� ����˴ϴ�.

	\param[in] name ��ü�� �̸��� ������ ���ڿ��Դϴ�.

	@see getName()
	*/
	virtual void				setName(const char* name)	= 0;

	/**
	\brief setName()���� ������ �̸� ���ڿ��� �˻��մϴ�.

	\return ��ü�� ���õ� �̸� ���ڿ��Դϴ�.

	@see setName()
	*/
	virtual const char*			getName()	const	= 0;

	/**
	\brief Deletes the joint.

	\note This call does not wake up the connected rigid bodies.
	*/
	virtual void				release()	= 0;

	/**
	\brief Retrieves the scene which this joint belongs to.

	\return Owner Scene. NULL if not part of a scene.

	@see PxScene
	*/
	virtual PxScene*			getScene()	const	= 0;

	void*						userData;	//!< user can assign this to whatever, usually to create a 1:1 relationship with a user object.

	//serialization

	/**
	\brief Put class meta data in stream, used for serialization
	*/
	static	void				getBinaryMetaData(PxOutputStream& stream);

	//~serialization
					
protected:
	virtual						~PxJoint() {}

	//serialization

	/**
	\brief Constructor
	*/
	PX_INLINE					PxJoint(PxType concreteType, PxBaseFlags baseFlags) : PxBase(concreteType, baseFlags), userData(NULL) {}
	
	/**
	\brief Deserialization constructor
	*/
	PX_INLINE					PxJoint(PxBaseFlags baseFlags)	: PxBase(baseFlags)	{}

	/**
	\brief Returns whether a given type name matches with the type of this instance
	*/
	virtual	bool				isKindOf(const char* name) const { PX_IS_KIND_OF(name, "PxJoint", PxBase); }

	//~serialization
};

class PxSpring
{
public:

	PxReal stiffness; //!< ����̺��� ������ ����: ��, ��ġ ������ ����ϴ� ��
	PxReal damping;   //!< ����̺��� ���� ����: ��, �ӵ� ������ ����ϴ� ��

	PxSpring(PxReal stiffness_, PxReal damping_): stiffness(stiffness_), damping(damping_) {}
};


#if !PX_DOXYGEN
} // namespace physx
#endif

/** \brief ������ ���� �������� �����ϴ� ���� �Լ�

	�� �Լ��� ���� SDK �������� ���� �Լ����� ��ü�մϴ�:

	void NxJointDesc::setGlobalAnchor(const NxVec3& wsAnchor);
	void NxJointDesc::setGlobalAxis(const NxVec3& wsAxis);

	�� �Լ��� ���� ���� �Է� �Ű������� ����Ͽ� ������ ���� ��� �����մϴ�.

	\param[in] wsAnchor ���� ������ ������ ��Ŀ ����. <b>����:</b> ��ġ ����
	\param[in] wsAxis ���� ������ ������ ��. <b>����:</b> ���� ����
	\param[in,out] joint ���� �������� �����ϴ� ����.
*/

PX_C_EXPORT void PX_CALL_CONV PxSetJointGlobalFrame(physx::PxJoint& joint, const physx::PxVec3* wsAnchor, const physx::PxVec3* wsAxis);

/** @} */
#endif
