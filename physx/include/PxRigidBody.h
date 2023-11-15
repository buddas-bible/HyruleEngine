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

#ifndef PX_RIGID_BODY_H
#define PX_RIGID_BODY_H
/** \addtogroup physics
@{
*/

#include "PxRigidActor.h"
#include "PxForceMode.h"
#include "PxNodeIndex.h"

#if !PX_DOXYGEN
namespace physx
{
#endif

/**
\brief Collection of flags describing the behavior of a rigid body.

@see PxRigidBody.setRigidBodyFlag(), PxRigidBody.getRigidBodyFlags()
*/
struct PxRigidBodyFlag
{
	enum Enum
	{
		/**
		\brief ���Ϳ� ���� Ű�׸�ƽ ��带 Ȱ��ȭ�մϴ�.

		Ű�׸�ƽ ���ʹ� ��(�߷°� ����)�� ������ ���� ������ ������� ���� Ư���� ���� �����Դϴ�.
		������ �������� ���ֵǸ� setKinematicTarget() �޼��带 ����Ͽ� ���迡�� �̵��� �� �ֽ��ϴ�.
		Ű�׸�ƽ ���ʹ� �Ϲ� ���� ���͸� �о ����� �� �ֽ��ϴ�.
		Ű�׸�ƽ ���ʹ� ���� �Ǵ� �ٸ� Ű�׸�ƽ ��ü�� �浹���� �ʽ��ϴ�.

		Ű�׸�ƽ ���ʹ� �����̴� �÷��� �Ǵ� ĳ���Ϳ� ���� �������� ������ ��� �ʿ��� ��쿡 �����մϴ�.

		����: �� �÷��׸� ���� ���Ϳ� �����ϸ� ���͸� �����ϰ��ϰ� �ӵ��� 0���� �����մϴ�.
		�� �÷��װ� �����Ǹ� ������ ���� ���� ���°� �����˴ϴ�.

		����: Ű�׸�ƽ ���ʹ� CCD(Continuous Collision Detection)�� ȣȯ���� �����Ƿ�
		�� �÷��׸� �����ϸ� �ڵ����� eENABLE_CCD�� ����ϴ�.

		@see PxRigidDynamic.setKinematicTarget()
		*/
		eKINEMATIC	= (1<<0),		//!< Enable kinematic mode for the body.

		/**
		\brief �� ������ ���� Ű�׸�ƽ Ÿ�� ��ȯ�� ����մϴ�.

		�� �÷��װ� ������ ��� �� ������ Ű�׸�ƽ Ÿ�� ��ȯ�� ���� ��ġ�� ó���մϴ� (���� ��ġ�� �ƴ�). �� �÷��װ� ������ Ű�׸�ƽ Ÿ���� �ùķ��̼� �ܰ� ���Ŀ��� �� ������ ������ ��Ĩ�ϴ�.

		@see PxRigidDynamic.setKinematicTarget()
		*/
		eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES	= (1<<1),

		/**
		\brief ������ ������Ʈ ������ Ȱ��ȭ�մϴ�.

		�� �÷��װ� �����ǰ� ������ CCD�� Ȱ��ȭ�� ���,
		�� ������ �浹�� ���� �ӵ��� �������� ����
		��ĥ �� �ִ� ���� �����ϱ� ���� CCD �ý��ۿ� ���� �ùķ��̼ǵ˴ϴ�.
		���� ���� ���� ������ �浹 ���͸����� PxPairFlag::eDETECT_CCD_CONTACT�� Ȱ��ȭ�ؾ� �ϸ�
		�̸� ���� CCD�� ���� ��ȣ �ۿ뿡 �����ϵ��� Ȱ��ȭ�Ǿ�� �մϴ�.

		����: Ű�׸�ƽ ���ʹ� CCD�� ȣȯ���� �����Ƿ� Ű�׸�ƽ ���Ϳ� ������ ��� �� �÷��״� �ڵ����� �������ϴ�.
		*/
		eENABLE_CCD	= (1<<2),		//!< Enable CCD for the body.

		/**
		\brief ������ ������Ʈ ���տ��� CCD�� Ȱ��ȭ�մϴ�.

		�� �÷��׸� �����ϰ� CCD�� Ȱ��ȭ�Ǹ� CCD ��ȣ �ۿ뿡�� ������ �ùķ��̼ǵ˴ϴ�.
		�⺻������ CCD ��ȣ �ۿ뿡�� ������ �ùķ��̼� ��Ƽ��Ʈ�� ������ ������ �����Ǿ����Ƿ� �⺻������ ��Ȱ��ȭ�˴ϴ�.
		CCD ������ ���� SDK �������� Ȱ��ȭ�Ǿ����ϴ�.
		�� �÷��׸� �����ϸ� ���� SDK ������ �� ������ ������ ���� �� �ֽ��ϴ�.

		����: �� �÷��׸� ����Ϸ��� PxRigidBodyFlag::eENABLE_CCD�� �����Ǿ� �־�� �մϴ�.
		*/
		eENABLE_CCD_FRICTION	= (1<<3),

		/**
		\brief ���͸� ����Ͽ� �ӵ��� ������� ���� �������� �������� �����ϵ��� �����մϴ�.
		�̸� ����Ͽ� CCD ȿ���� ���� �� �ֽ��ϴ�.

		eENABLE_CCD �� eENABLE_SPECULATIVE_CCD �� �÷��װ� ������ ���Ϳ� �����Ǿ� �ִ� ���
		���� ����� ������ ����(eENABLE_SPECULATIVE_CCD)�� ���� ó���ǰ�
		���� ����� ������Ʈ(eENABLE_CCD)�� ���� ó���˴ϴ�.
		*/
		eENABLE_SPECULATIVE_CCD	= (1<<4),

		/**
		\brief �ùķ��̼ǿ��� ��ü�� �ڼ� ��ȭ�� ���� �ܰ迡�� ������ �� �ֵ��� ��ü�� ����մϴ�.

		��ü�� ���ο� �ڼ��� ������ ���� �׼����ϴ� ���� ������ ��찡 ������
		fetchResults() ȣ���� ��ȯ�� ������ ��ٸ� �ʿ䰡 �����ϴ�. 
		�� �÷��׸� �����ϸ� ��ü�� #PxSimulationEventCallback::onAdvance()���� ����ǵ��� ����˴ϴ�. 
		�� ����� ���� �� ���� ������ �����ϱ� ���� �ش� �ݹ��� ������ �����Ͻʽÿ�.

		@see PxSimulationEventCallback::onAdvance()
		*/
		eENABLE_POSE_INTEGRATION_PREVIEW	= (1<<5),

		/**
		\brief CCD�� maxContactImpulse�� �����ϵ��� ����մϴ�.
		�ı� �ý��۰� ���� ��� ��ʿ� ����������
		�ð��� ��Ƽ��Ʈ�� ������ �� �����Ƿ� �⺻������ Ȱ��ȭ���� �ʽ��ϴ�.
		*/
		eENABLE_CCD_MAX_CONTACT_IMPULSE = (1<<6),

		/**
		\brief �� �� ���ӵ��� ������ ���� ������ �ʰ� �ű�ϴ�.
		*/
		eRETAIN_ACCELERATIONS = (1<<7),

		/**
		\brief �� Actor�� ���� Ű�׸�ƽ-Ű�׸�ƽ �� �˸��� ������ Ȱ��ȭ�մϴ�.

		�� �÷��״� Ű�׸�ƽ ���Ϳ� ���� ���� ��� ������ PxPairFilteringMode ������ �����մϴ�.
		�̰��� �� Actor�� ������ �ֿ� ���� PxPairFilteringMode::eKEEP�� �����մϴ�.

		��κ��� ��� �ټ��� Ű�׸�ƽ ���Ͱ� ������ ��� ���� ���� ��ȣ �ۿ뿡�� ������ �ִ� ��쿡 �����մϴ�.
		�� ���, PxSceneDesc.kineKineFilteringMode = PxPairFilteringMode::eKILL�� ����ϰ�
		�˸��� �ʿ��� �Ҽ��� Ű�׸�ƽ ���Ϳ� eFORCE_KINE_KINE_NOTIFICATIONS �÷��׸� �����ϴ� ���� �����ϴ�.

		����: PxRigidBodyFlag::eKINEMATIC�� �������� ���� ��쿡�� ȿ���� �����ϴ�.

		���: �� �÷��׸� ���� �߿� �����ϴ��� ���͸� ��鿡�� ������ ���� �ٽ� �߰����� ������ ȿ���� �����ϴ�.

		����: PxPairFilteringMode PxSceneDesc.kineKineFilteringMode
		*/
		eFORCE_KINE_KINE_NOTIFICATIONS = (1<<8),

		/**
		\brief �� Actor�� ���� ����-Ű�׸�ƽ �� �˸��� ������ Ȱ��ȭ�մϴ�.

		�̰��� ����-Ű�׸�ƽ ��ȣ �ۿ뿡 ���� eFORCE_KINE_KINE_NOTIFICATIONS�� ����������
		����-Ű�׸�ƽ ��ȣ �ۿ뿡 ���� ���Դϴ�.

		����: PxRigidBodyFlag::eKINEMATIC�� �������� ���� ��� ȿ���� �����ϴ�.

		���: �� �÷��׸� ���� �߿� �����ϴ��� ���͸� ��鿡�� ������ ���� �ٽ� �߰����� ������ ȿ���� �����ϴ�.

		����: PxPairFilteringMode PxSceneDesc.staticKineFilteringMode
		*/
		eFORCE_STATIC_KINE_NOTIFICATIONS = (1<<9),

		/**
		\brief �� ������ �ٵ� ���� ���̷ν����� �� ����� Ȱ��ȭ�մϴ�.
		*/
		eENABLE_GYROSCOPIC_FORCES = (1<<10),

		/**
		\brief ���� �뵵
		*/
		eRESERVED = (1<<15)
	};
};

/**
\brief collection of set bits defined in PxRigidBodyFlag.

@see PxRigidBodyFlag
*/
typedef PxFlags<PxRigidBodyFlag::Enum,PxU16> PxRigidBodyFlags;
PX_FLAGS_OPERATORS(PxRigidBodyFlag::Enum,PxU16)

/**
\brief PxRigidBody is a base class shared between dynamic rigid body objects.

@see PxRigidActor
*/

class PxRigidBody : public PxRigidActor
{
public:
	// Runtime modifications

/************************************************************************************************/
/** @name Mass Manipulation
*/

	/**
	\brief ���Ϳ� ���� ���� �߽� ��ġ�� ���Ϳ� ��������� �����մϴ�.

	����: �� ��ȯ�� �����ϴ��� ���͸� ���忡�� �̵���Ű���� �ʽ��ϴ�!

	����: ������ �������� �ʴ� ���� �߽��� �����ϸ� SDK�� ���� ������ �ذ��ϴ� �� ������� ���� �� �ֽ��ϴ�.
	���� �Ҿ������� ���� ������ ������ �� �ֽ��ϴ�.

	����: �� ��ȯ�� �����ϴ��� getLinearVelocity()�� ���� ����Ǵ� ���� �ӵ��� ���� �߽��� �̵��� ����Ͽ� ������Ʈ���� �ʽ��ϴ�.
	�̵��� �ݿ��ؾ� �ϴ� ��� ����ڴ� setLinearVelocity()�� ����Ͽ� �ӵ��� ������Ʈ�ؾ� �մϴ�.

	<b>�⺻��:</b> �׵� ��ȯ

	\param[in] pose ���� �������� �������� �� ���� �߽� ������ ��ȯ. <b>����:</b> ��ü �� ��ȯ.

	@see getCMassLocalPose() getLinearVelocity()
	*/
	virtual		void	setCMassLocalPose(const PxTransform& pose) = 0;

	/**
	\brief ���� �������� �������� �� ���� �߽� ��ġ�� �˻��մϴ�.

	\return ���� �������� �������� �� ���� �߽� ��ġ.

	@see setCMassLocalPose()
	*/
	virtual		PxTransform 	getCMassLocalPose() const = 0;

	/**
	\brief ���� ������ ������ �����մϴ�.

	������ ������� �մϴ�.

	setMass()�� ��ü�� ���� Ư���� ������Ʈ���� ������,
	���� �ټ��� �����Ϸ��� setMassSpaceInertiaTensor() �Ǵ�
	PhysX Ȯ�� �޼��� #PxRigidBodyExt::updateMassAndInertia()�� ����ϼ���.

	����: ���� 0�� ��� ���� �������� �ؼ��˴ϴ�.
	����: PxArticulationLink�� ��� ���� 0�� ������ ������ PxRigidDynamic�� ��� ���˴ϴ�.

	<b>�⺻��:</b> 1.0

	<b>����:</b> �ڵ����� ���͸� ������ <b>�ʽ��ϴ�</b>.

	\param[in] mass ������ �� ���� ��. <b>����:</b> [0, PX_MAX_F32)

	@see getMass() setMassSpaceInertiaTensor()
	*/
	virtual		void	setMass(PxReal mass) = 0;

	/**
	\brief ������ ������ �˻��մϴ�.

	����: ���� 0�� ��� ���� �������� �ؼ��˴ϴ�.

	\return �� ������ ����.

	@see setMass() setMassSpaceInertiaTensor()
	*/
	virtual		PxReal	getMass() const = 0;

	/**
	\brief ������ �� ������ �˻��մϴ�.

	\return �� ������ �� ����.

	@see setMass() setMassSpaceInertiaTensor()
	*/
	virtual		PxReal	getInvMass() const = 0;

	/**
	\brief ���� ���� ��ǥ�� ������ �Ű������� ����Ͽ� ���� �ټ��� �����մϴ�.

	�̷��� ����� �밢�� ����Դϴ�. ���޵� ���ʹ� �밢���Դϴ�.

	���� ��밢�� ����/���� ���� ���� �ټ�(3x3 ���)�� �ִ� ���, �̸� �밢ȭ�ϰ� ������ ���� ���� ��ȯ�� �����ؾ� �մϴ�.
	#setCMassLocalPose()�� �����ϼ���.

	���� �ټ� ��Ҵ� ������� �մϴ�.

	����: ��� �� �ϳ��� 0�� ��� �ش� ���� ���� ������ �������� �ؼ��˴ϴ�.
	����: PxArticulationLink�� ��� 0 ���� ������ ������ PxRigidDynamic�� ��� ���˴ϴ�.

	<b>�⺻��:</b> (1.0, 1.0, 1.0)

	<b>����:</b> �ڵ����� ���͸� ������ <b>�ʽ��ϴ�</b>.

	\param[in] m ������ �� ���� ���� ���� �ټ�.

	@see getMassSpaceInertia() setMass() setCMassLocalPose()
	*/
	virtual		void	setMassSpaceInertiaTensor(const PxVec3& m) = 0;

	/**
	\brief ���Ϳ� ���� ���� ��ǥ �����Ӱ� ���õ� �밢 ���� �ټ��� �˻��մϴ�.

	�� �޼���� ���� ��ǥ ������ ���� ���͸� �˻��մϴ�.

	\return �� ������ ���� ���� ���� �ټ�.

	����: ��� �� �ϳ��� 0�� ��� �ش� ���� ���� ������ �������� �ؼ��˴ϴ�.

	@see setMassSpaceInertiaTensor() setMass() setCMassLocalPose()
	*/
	virtual		PxVec3	getMassSpaceInertiaTensor()			const = 0;

	/**
	\brief ���Ϳ� ���� ���� ��ǥ �����Ӱ� ���õ� �밢 �� ���� �ټ��� �˻��մϴ�.

	�� �޼���� ���� ��ǥ ������ �� ���� ���͸� �˻��մϴ�.

	����: ��� �� �ϳ��� 0�� ��� �ش� ���� ���� ������ �������� �ؼ��˴ϴ�.

	\return �� ������ ���� ���� �� ���� �ټ�.

	@see setMassSpaceInertiaTensor() setMass() setCMassLocalPose()
	*/
	virtual		PxVec3	getMassSpaceInvInertiaTensor()			const = 0;

	/************************************************************************************************/
	/** @name Damping
	*/

	/**
	\brief ���� ���� ����� �����մϴ�.

	0�� ���谡 ������ ��Ÿ���ϴ�. ���� ����� ������� �մϴ�.

	<b>�⺻��:</b> PxArticulationLink�� ��� 0.05, PxRigidDynamic�� ��� 0.0

	\param[in] linDamp ���� ���� ���. <b>����:</b> [0, PX_MAX_F32)

	@see getLinearDamping() setAngularDamping()
	*/
	virtual		void	setLinearDamping(PxReal linDamp) = 0;

	/**
	\brief ���� ���� ����� �˻��մϴ�.

	\return �� ���Ϳ� ���õ� ���� ���� ���.

	@see setLinearDamping() getAngularDamping()
	*/
	virtual		PxReal	getLinearDamping() const = 0;

	/**
	\brief ���� ���� ����� �����մϴ�.

	0�� ���谡 ������ ��Ÿ���ϴ�. ���� ���� ����� ������� �մϴ�.

	<b>�⺻��:</b> 0.05

	\param[in] angDamp ���� ���� ���. <b>����:</b> [0, PX_MAX_F32)

	@see getAngularDamping() setLinearDamping()
	*/
	virtual		void	setAngularDamping(PxReal angDamp) = 0;

	/**
	\brief ���� ���� ����� �˻��մϴ�.

	\return �� ���Ϳ� ���õ� ���� ���� ���.

	@see setAngularDamping() getLinearDamping()
	*/
	virtual		PxReal	getAngularDamping() const = 0;


/************************************************************************************************/
/** @name Velocity
*/

	/**
	\brief Retrieves the linear velocity of an actor.

	\note It is not allowed to use this method while the simulation is running (except during PxScene::collide(),
	in PxContactModifyCallback or in contact report callbacks).

	\note The linear velocity is reported with respect to the rigid body's center of mass and not the actor frame origin.

	\return The linear velocity of the actor.

	@see PxRigidDynamic.setLinearVelocity() getAngularVelocity()
	*/
	virtual		PxVec3	getLinearVelocity()		const = 0;

	/**
	\brief Retrieves the angular velocity of the actor.

	\note It is not allowed to use this method while the simulation is running (except during PxScene::collide(),
	in PxContactModifyCallback or in contact report callbacks).

	\return The angular velocity of the actor.

	@see PxRigidDynamic.setAngularVelocity() getLinearVelocity() 
	*/
	virtual		PxVec3	getAngularVelocity()	const = 0;

	/**
	\brief �� ���Ϳ� ���Ǵ� �ִ� ���� �ӵ��� ������ �� �ֽ��ϴ�.

	�� �Լ��� ����Ͽ� �� ��ü �ٵ�(Rigid Body)�� ���Ǵ� �ִ� ���� �ӵ��� ������ �� �ֽ��ϴ�.
	�� ���� ���� �ӵ��� �� ������ ���ѵ˴ϴ�.

	����: ���� �ӵ��� ������ �� ������ �ֹ� �տ��� Ŭ����(clamping)�ǹǷ�,
	������ �Ͻ������� �ʰ��� �� �ֽ��ϴ�.

	<b>�⺻��:</b> PxArticulationLink�� ��� 100 * PxTolerancesScale::length, PxRigidDynamic�� ��� 1e^16

	\param[in] maxLinVel ���Ϳ� ���� �ִ� ��� ���� �ӵ�. <b>����:</b> [0, 1e^16)

	@see getMaxAngularVelocity()
	*/
	virtual		void	setMaxLinearVelocity(PxReal maxLinVel) = 0;

	/**
	\brief Retrieves the maximum angular velocity permitted for this actor.

	\return The maximum allowed angular velocity for this actor.

	@see setMaxLinearVelocity
	*/
	virtual		PxReal	getMaxLinearVelocity()	const = 0;

	/**
	\brief �� ���Ϳ� ���Ǵ� �ִ� ���ӵ��� ������ �� �ֽ��ϴ�.

	�پ��� ���� ����� ���� �ſ� ������ ȸ���ϴ� ���ʹ� �ùķ��̼ǿ� ������ �����ϸ�,
	�̷� ���� ������ �ʴ� ����� �߻��� �� �ֽ��ϴ�.

	�� �Լ��� ����Ͽ� �� ��ü �ٵ� ���Ǵ� �ִ� ���ӵ��� ������ �� �ֽ��ϴ�.
	�� ���� ���ӵ��� �� ������ ���ѵ˴ϴ�.

	����: ���ӵ��� ������ �� ������ �ֹ� �տ��� Ŭ����(clamping)�ǹǷ�,
	������ �Ͻ������� �ʰ��� �� �ֽ��ϴ�.

	<b>�⺻��:</b> PxArticulationLink�� ��� 50.0, PxRigidDynamic�� ��� 100.0

	<b>����:</b> [0, 1e^16)

	\param[in] maxAngVel ���Ϳ� ���� �ִ� ��� ���ӵ�.

	@see getMaxAngularVelocity()
	*/
	virtual		void	setMaxAngularVelocity(PxReal maxAngVel) = 0;

	/**
	\brief �� ���Ϳ� ���� �ִ� ���ӵ��� �˻��մϴ�.

	\return �� ���Ϳ� ���� �ִ� ��� ���ӵ�.

	@see setMaxAngularVelocity
	*/
	virtual		PxReal	getMaxAngularVelocity()	const = 0;

/************************************************************************************************/
/** @name Forces
*/

	/**
	\brief ������ ���� �߽ɿ� ���ǵ� �۷ι� ��ǥ �����ӿ��� ��(�Ǵ� ���)�� �����մϴ�.

	<b>�̰��� ȸ������ �������� �ʽ��ϴ�</b>.

	::PxForceMode�� ���� �Ϲ����� �� �Ǵ� ��������� �����մϴ�.

	�� ���ʹ� ���ӵ� �� �ӵ� ���� �����(accumulator)�� ���� �����մϴ�.
	���ӵ� �� �ӵ� ���濡 ���� ���� ���� PxForceMode::eACCELERATION �� PxForceMode::eVELOCITY_CHANGE�� ����մϴ�.
	PxForceMode::eFORCE �� PxForceMode::eIMPULSE ��嵵 ������ ����⸦ �����ϸ�,
	�ܼ��� �� �������� ���� �Ű������� ���ϰ� PxForceMode::eACCELERATION �� PxForceMode::eVELOCITY_CHANGE�� ���� ����մϴ�.

	����: �� �޼���� ���Ͱ� �̹� �ùķ��̼ǿ� �߰����� �ʾҰų� PxActorFlag::eDISABLE_SIMULATION�� ������ ��쿡 ����� �� �����ϴ�.

	����: PxForceMode::eIMPULSE �� PxForceMode::eVELOCITY_CHANGE ���� ��Ƽŧ���̼� ��ũ�� ������ �� �����ϴ�.

	����: �̰��� ��Ƽŧ���̼� ��ũ���� ȣ��� ��� ��ũ�� ������Ʈ�Ǹ� ��ü ��Ƽŧ���̼��� ������Ʈ���� �ʽ��ϴ�.

	����: impulsive force�� ���뿡�� �߻��ϴ� ���� �ӵ� ������ ����ϴ� ����� ���� �ڼ��� ������
	#PxRigidBodyExt::computeVelocityDeltaFromImpulse�� �����Ͻʽÿ�. ���⼭ �������� ���� ���� Ÿ�ӽ������� ���� ���Դϴ�.

	<b>����:</b> �� ȣ���� ���Ͱ� �ڰ� ������ �����, autowake �Ű������� true(�⺻��)�̰ų� ���� 0�̸� ����ϴ�.

	\param[in] force �۷ι� �����ӿ��� ���ǵ� ������ ��/���.
	\param[in] mode ��/����� ������ �� ����� ���(����: #PxForceMode)
	\param[in] autowake ���� �ڰ� �ִ� ���͸� ������ ���θ� �����մϴ�. true�̰� ���� ���� �ִ� ī���� ����
	#PxSceneDesc::wakeCounterResetValue���� ������ reset ������ �����մϴ�.

	@see PxForceMode addTorque
	*/
	virtual		void	addForce(const PxVec3& force, PxForceMode::Enum mode = PxForceMode::eFORCE, bool autowake = true) = 0;

	/**
	\brief ���Ϳ� ���ǵ� �۷ι� ��ǥ �����ӿ��� ������ ���� ȸ�� ��ũ�� �����մϴ�.

	::PxForceMode�� ��ũ�� �������� ��ũ���� �������� ��ũ������ �����մϴ�.

	�� ���ʹ� �� ���ӵ� �� ���ӵ� ���� �����(accumulator)�� ���� �����մϴ�.
	�� ���ӵ� �� ���ӵ� ���濡 ���� ���� ���� PxForceMode::eACCELERATION �� PxForceMode::eVELOCITY_CHANGE�� ����մϴ�.
	PxForceMode::eFORCE �� PxForceMode::eIMPULSE ��嵵 ������ ����⸦ �����ϸ�,
	�ܼ��� ���� �Ű������� �� �������� ���� ���� PxForceMode::eACCELERATION �� PxForceMode::eVELOCITY_CHANGE�� ���� ����մϴ�.

	����: �� �޼���� ���Ͱ� �̹� �ùķ��̼ǿ� �߰����� �ʾҰų� PxActorFlag::eDISABLE_SIMULATION�� ������ ��쿡 ����� �� �����ϴ�.

	����: PxForceMode::eIMPULSE �� PxForceMode::eVELOCITY_CHANGE ���� ��Ƽŧ���̼� ��ũ�� ������ �� �����ϴ�.

	����: �̰��� ��Ƽŧ���̼� ��ũ���� ȣ��� ��� ��ũ�� ������Ʈ�Ǹ� ��ü ��Ƽŧ���̼��� ������Ʈ���� �ʽ��ϴ�.

	����: ���� ȸ�� ��ũ�� �����ϴ� �� ���� ���ӵ� ������ ����ϴ� ����� ���� �ڼ��� ������
	#PxRigidBodyExt::computeVelocityDeltaFromImpulse�� �����Ͻʽÿ�. ���⼭ ���� ȸ�� ��ũ�� �ð� �ܰ�� ���� ���� ��ũ�Դϴ�.

	<b>����:</b> �� ȣ���� ���Ͱ� �ڰ� ������ �����, autowake �Ű������� true(�⺻��)�̰ų� ��ũ�� 0�̸� ����ϴ�.

	\param[in] torque �۷ι� �����ӿ��� ���ǵ� ������ ��ũ. <b>����:</b> ��ũ ����
	\param[in] mode ��/����� ������ �� ����� ���(����: #PxForceMode).
	\param[in] autowake ���� �ڰ� �ִ� ���͸� ������ ���θ� �����մϴ�. true�̰� ���� ���� �ִ� ī���� ����
	#PxSceneDesc::wakeCounterResetValue���� ������ reset ������ �����մϴ�.

	@see PxForceMode addForce()
	*/
	virtual		void	addTorque(const PxVec3& torque, PxForceMode::Enum mode = PxForceMode::eFORCE, bool autowake = true) = 0;

	/**
	\brief ������ ���� �����(������ ���� ���η� ����)�մϴ�.

	�� ���ʹ� ���ӵ� �� �ӵ� ���� �����(accumulator)�� ���� �����մϴ�.
	�� ���ӵ� �� �ӵ� ���濡 ���� ���� ���� PxForceMode::eACCELERATION �� PxForceMode::eVELOCITY_CHANGE�� ����մϴ�.
	PxForceMode::eFORCE �� PxForceMode::eIMPULSE ��嵵 ������ ����⸦ �����ϸ�(�ڼ��� ������ PxRigidBody::addForce() ����),
	���� clearForce(PxForceMode::eFORCE)�� ȣ���ϴ� ȿ���� clearForce(PxForceMode::eACCELERATION)�� ȣ���ϴ� �Ͱ� �����ϸ�,
	clearForce(PxForceMode::eIMPULSE)�� ȣ���ϴ� ȿ���� clearForce(PxForceMode::eVELOCITY_CHANGE)�� ȣ���ϴ� �Ͱ� �����մϴ�.

	::PxForceMode�� ������ ���� �������� ������ �������� �������� �����մϴ�.

	����: PxForceMode::eIMPULSE �� PxForceMode::eVELOCITY_CHANGE ���� ��Ƽŧ���̼� ��ũ�� ������ �� �����ϴ�.

	����: �� �޼���� ���Ͱ� �̹� �ùķ��̼ǿ� �߰����� �ʾҰų� PxActorFlag::eDISABLE_SIMULATION�� ������ ��쿡 ����� �� �����ϴ�.

	\param[in] mode ��/����� ���� �� ����� ���(����: #PxForceMode)

	@see PxForceMode addForce
	*/
	virtual		void	clearForce(PxForceMode::Enum mode = PxForceMode::eFORCE) = 0;

	/**
	\brief ���Ϳ� ���ǵ� �۷ι� ��ǥ �����ӿ��� ���� ȸ�� ��ũ�� ����ϴ�.

	::PxForceMode�� ������ ��ũ�� �������� ��ũ���� �������� ��ũ������ �����մϴ�.

	�� ���ʹ� �� ���ӵ� �� ���ӵ� ���� �����(accumulator)�� ���� �����մϴ�.
	�� ���ӵ� �� ���ӵ� ���濡 ���� ���� ���� PxForceMode::eACCELERATION �� PxForceMode::eVELOCITY_CHANGE�� ����մϴ�.
	PxForceMode::eFORCE �� PxForceMode::eIMPULSE ��嵵 ������ ����⸦ �����ϸ�(�ڼ��� ������ PxRigidBody::addTorque() ����),
	���� clearTorque(PxForceMode::eFORCE)�� ȣ���ϴ� ȿ���� clearTorque(PxForceMode::eACCELERATION)�� ȣ���ϴ� �Ͱ� �����ϸ�,
	clearTorque(PxForceMode::eIMPULSE)�� ȣ���ϴ� ȿ���� clearTorque(PxForceMode::eVELOCITY_CHANGE)�� ȣ���ϴ� �Ͱ� �����մϴ�.

	::PxForceMode�� ������ ��ũ�� �������� ��ũ���� �������� ��ũ������ �����մϴ�.

	����: PxForceMode::eIMPULSE �� PxForceMode::eVELOCITY_CHANGE ���� ��Ƽŧ���̼� ��ũ�� ������ �� �����ϴ�.

	����: �� �޼���� ���Ͱ� �̹� �ùķ��̼ǿ� �߰����� �ʾҰų� PxActorFlag::eDISABLE_SIMULATION�� ������ ��쿡 ����� �� �����ϴ�.

	\param[in] mode ��ũ/����� ���� �� ����� ���(����: #PxForceMode).

	@see PxForceMode addTorque
	*/
	virtual		void	clearTorque(PxForceMode::Enum mode = PxForceMode::eFORCE) = 0;

	/**
	\brief Sets the impulsive force and torque defined in the global coordinate frame to the actor.

	::PxForceMode determines if the cleared torque is to be conventional or impulsive.

	\note The force modes PxForceMode::eIMPULSE and PxForceMode::eVELOCITY_CHANGE can not be applied to articulation links.

	\note It is invalid to use this method if the actor has not been added to a scene already or if PxActorFlag::eDISABLE_SIMULATION is set.

	@see PxForceMode addTorque
	*/
	virtual		void	setForceAndTorque(const PxVec3& force, const PxVec3& torque, PxForceMode::Enum mode = PxForceMode::eFORCE) = 0;

	/**
	\brief Raises or clears a particular rigid body flag.
	
	See the list of flags #PxRigidBodyFlag

	<b>Default:</b> no flags are set

	<b>Sleeping:</b> Does <b>NOT</b> wake the actor up automatically.

	\param[in] flag		The PxRigidBody flag to raise(set) or clear. See #PxRigidBodyFlag.
	\param[in] value	The new boolean value for the flag.

	@see PxRigidBodyFlag getRigidBodyFlags() 
	*/
	virtual		void	setRigidBodyFlag(PxRigidBodyFlag::Enum flag, bool value) = 0;
	virtual		void	setRigidBodyFlags(PxRigidBodyFlags inFlags) = 0;

	/**
	\brief Reads the PxRigidBody flags.
	
	See the list of flags #PxRigidBodyFlag

	\return The values of the PxRigidBody flags.

	@see PxRigidBodyFlag setRigidBodyFlag()
	*/
	virtual		PxRigidBodyFlags	getRigidBodyFlags()	const = 0;

	/**
	\brief Sets the CCD minimum advance coefficient.

	The CCD minimum advance coefficient is a value in the range [0, 1] that is used to control the minimum amount of time a body is integrated when
	it has a CCD contact. The actual minimum amount of time that is integrated depends on various properties, including the relative speed and collision shapes
	of the bodies involved in the contact. From these properties, a numeric value is calculated that determines the maximum distance (and therefore maximum time) 
	which these bodies could be integrated forwards that would ensure that these bodies did not pass through each-other. This value is then scaled by CCD minimum advance
	coefficient to determine the amount of time that will be consumed in the CCD pass.

	<b>Things to consider:</b> 
	A large value (approaching 1) ensures that the objects will always advance some time. However, larger values increase the chances of objects gently drifting through each-other in
	scenes which the constraint solver can't converge, e.g. scenes where an object is being dragged through a wall with a constraint.
	A value of 0 ensures that the pair of objects stop at the exact time-of-impact and will not gently drift through each-other. However, with very small/thin objects initially in 
	contact, this can lead to a large amount of time being dropped and increases the chances of jamming. Jamming occurs when the an object is persistently in contact with an object 
	such that the time-of-impact is	0, which results in no time being advanced for those objects in that CCD pass.

	The chances of jamming can be reduced by increasing the number of CCD mass @see PxSceneDesc.ccdMaxPasses. However, increasing this number increases the CCD overhead.

	\param[in] advanceCoefficient The CCD min advance coefficient. <b>Range:</b> [0, 1] <b>Default:</b> 0.15
	*/
	virtual void setMinCCDAdvanceCoefficient(PxReal advanceCoefficient) = 0;

	/**
	\brief Gets the CCD minimum advance coefficient.

	\return The value of the CCD min advance coefficient.

	@see setMinCCDAdvanceCoefficient
	*/
	virtual PxReal getMinCCDAdvanceCoefficient() const = 0;

	/**
	\brief Sets the maximum depenetration velocity permitted to be introduced by the solver.
	This value controls how much velocity the solver can introduce to correct for penetrations in contacts. 
	\param[in] biasClamp The maximum velocity to de-penetrate by <b>Range:</b> (0, PX_MAX_F32].
	*/
	virtual void setMaxDepenetrationVelocity(PxReal biasClamp) = 0;

	/**
	\brief Returns the maximum depenetration velocity the solver is permitted to introduced.
	This value controls how much velocity the solver can introduce to correct for penetrations in contacts. 
	\return The maximum penetration bias applied by the solver.
	*/
	virtual PxReal getMaxDepenetrationVelocity() const = 0;

	/**
	\brief Sets a limit on the impulse that may be applied at a contact. The maximum impulse at a contact between two dynamic or kinematic
	bodies will be the minimum	of the two limit values. For a collision between a static and a dynamic body, the impulse is limited
	by the value for the dynamic body.

	\param[in] maxImpulse the maximum contact impulse. <b>Range:</b> [0, PX_MAX_F32] <b>Default:</b> PX_MAX_F32

	@see getMaxContactImpulse
	*/
	virtual void setMaxContactImpulse(PxReal maxImpulse) = 0;

	/**
	\brief Returns the maximum impulse that may be applied at a contact.

	\return The maximum impulse that may be applied at a contact

	@see setMaxContactImpulse
	*/
	virtual PxReal getMaxContactImpulse() const = 0;

	/**
	\brief Sets a distance scale whereby the angular influence of a contact on the normal constraint in a contact is 
	zeroed if normal.cross(offset) falls below this tolerance. Rather than acting as an absolute value, this tolerance
	is scaled by the ratio rXn.dot(angVel)/normal.dot(linVel) such that contacts that have relatively larger angular velocity
	than linear normal velocity (e.g. rolling wheels) achieve larger slop values as the angular velocity increases.

	\param[in] slopCoefficient the Slop coefficient. <b>Range:</b> [0, PX_MAX_F32] <b>Default:</b> 0

	@see getContactSlopCoefficient
	*/
	virtual void setContactSlopCoefficient(PxReal slopCoefficient) = 0;

	/**
	\brief Returns the contact slop coefficient.

	\return The contact slop coefficient.

	@see setContactSlopCoefficient
	*/
	virtual PxReal getContactSlopCoefficient() const = 0;

	/**
	\brief Returns the island node index

	\return The island node index.
	*/
	virtual PxNodeIndex getInternalIslandNodeIndex() const = 0;

protected:
	PX_INLINE			PxRigidBody(PxType concreteType, PxBaseFlags baseFlags) : PxRigidActor(concreteType, baseFlags) {}
	PX_INLINE			PxRigidBody(PxBaseFlags baseFlags) : PxRigidActor(baseFlags) {}
	virtual				~PxRigidBody()	{}
	virtual		bool	isKindOf(const char* name)	const	{ PX_IS_KIND_OF(name, "PxRigidBody", PxRigidActor); }
};

#if !PX_DOXYGEN
} // namespace physx
#endif

/** @} */
#endif
