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

#ifndef PX_MATERIAL_H
#define PX_MATERIAL_H
/** \addtogroup physics
@{
*/

#include "PxBaseMaterial.h"

#if !PX_DOXYGEN
namespace physx
{
#endif

class PxScene;

/**
\brief Flags which control the behavior of a material.

@see PxMaterial 
*/
struct PxMaterialFlag
{
	enum Enum
	{
		/**
		\brief If this flag is set, friction computations are always skipped between shapes with this material and any other shape.
		*/
		eDISABLE_FRICTION = 1 << 0,

		/**
		\brief Whether to use strong friction.
		The difference between "normal" and "strong" friction is that the strong friction feature
		remembers the "friction error" between simulation steps. The friction is a force trying to
		hold objects in place (or slow them down) and this is handled in the solver. But since the
		solver is only an approximation, the result of the friction calculation can include a small
		"error" - e.g. a box resting on a slope should not move at all if the static friction is in
		action, but could slowly glide down the slope because of a small friction error in each 
		simulation step. The strong friction counter-acts this by remembering the small error and
		taking it to account during the next simulation step.

		However, in some cases the strong friction could cause problems, and this is why it is
		possible to disable the strong friction feature by setting this flag. One example is
		raycast vehicles that are sliding fast across the surface, but still need a precise
		steering behavior. It may be a good idea to reenable the strong friction when objects
		are coming to a rest, to prevent them from slowly creeping down inclines.

		Note: This flag only has an effect if the PxMaterialFlag::eDISABLE_FRICTION bit is 0.
		*/
		eDISABLE_STRONG_FRICTION = 1 << 1,

		/**
		\brief Whether to correct the friction force applied by the patch friction model to better match analytical models.
		This flag only has an effect if the PxFrictionType::ePATCH friction model is used.

		When using the patch friction model, up to two friction anchors are generated per patch. The normal force of all contacts
		in the patch is accumulated and equally distributed among the anchors in order to compute friction forces. If this flag
		is disabled, the legacy behavior is active which produces double the expected friction force in the case of two anchors,
		since the full accumulated normal force is used in both anchors for the friction computation.
		*/
		eIMPROVED_PATCH_FRICTION = 1 << 2,

		/**
		\brief This flag has the effect of enabling an implicit spring model for the normal force computation.
		@see PxMaterial.setRestitution, PxMaterial.setDamping
		*/
		eCOMPLIANT_CONTACT = 1 << 3
	};
};

/**
\brief collection of set bits defined in PxMaterialFlag.

@see PxMaterialFlag
*/
typedef PxFlags<PxMaterialFlag::Enum,PxU16> PxMaterialFlags;
PX_FLAGS_OPERATORS(PxMaterialFlag::Enum,PxU16)


/**
\brief �� ���� �Ӽ��� �浹�� ���� �Ǵ� �ݹ߷� ����� �����ϱ� ���� ���յǴ� ����� �����ϴ� �������Դϴ�.

�� ���� ���Ͱ� ���� ������ ��, ������ �پ��� ����� ���� ������ ��������, 
�츮�� �� �� ���Ϳ� ���� �ϳ��� ��� ���ո� �ʿ��մϴ�.

�������� ����� ������ ��ʺ��� ���������� �����Ǳ� ������ ������ ������ ������ �ʽ��ϴ�. 
�׷��� �̸� �ֺ� ��ȸ ���̺�� �ùķ��̼��ϴ� ���� ���� ���������Դϴ�.

�̷��� ������ ������ ���� ���� ������ �����˴ϴ�:

eAVERAGE
eMIN
eMULTIPLY
eMAX

���� ȿ������ ���� ���� maximum(material0.combineMode, material1.combineMode)�Դϴ�.

@see PxMaterial.setFrictionCombineMode() PxMaterial.getFrictionCombineMode() PxMaterial.setRestitutionCombineMode() PxMaterial.getFrictionCombineMode()
*/
struct PxCombineMode
{
	enum Enum
	{
		eAVERAGE	= 0,		//!< Average: (a + b)/2
		eMIN		= 1,		//!< Minimum: minimum(a,b)
		eMULTIPLY	= 2,		//!< Multiply: a*b
		eMAX		= 3,		//!< Maximum: maximum(a,b)
		eN_VALUES	= 4,		//!< This is not a valid combine mode, it is a sentinel to denote the number of possible values. We assert that the variable's value is smaller than this.
		ePAD_32		= 0x7fffffff //!< This is not a valid combine mode, it is to assure that the size of the enum type is big enough.
	};
};

/**
\brief Material class to represent a set of surface properties. 

@see PxPhysics.createMaterial
*/
class PxMaterial : public PxBaseMaterial
{
public:

	/**
	\brief Sets the coefficient of dynamic friction.
	
	The coefficient of dynamic friction should be in [0, PX_MAX_F32). If set to greater than staticFriction, the effective value of staticFriction will be increased to match.

	<b>Sleeping:</b> Does <b>NOT</b> wake any actors which may be affected.

	\param[in] coef Coefficient of dynamic friction. <b>Range:</b> [0, PX_MAX_F32)

	@see getDynamicFriction()
	*/
	virtual		void	setDynamicFriction(PxReal coef) = 0;

	/**
	\brief Retrieves the DynamicFriction value.

	\return The coefficient of dynamic friction.

	@see setDynamicFriction
	*/
	virtual		PxReal	getDynamicFriction() const = 0;

	/**
	\brief Sets the coefficient of static friction
	
	The coefficient of static friction should be in the range [0, PX_MAX_F32)

	<b>Sleeping:</b> Does <b>NOT</b> wake any actors which may be affected.

	\param[in] coef Coefficient of static friction. <b>Range:</b> [0, PX_MAX_F32)

	@see getStaticFriction() 
	*/
	virtual		void	setStaticFriction(PxReal coef) = 0;

	/**
	\brief Retrieves the coefficient of static friction.
	\return The coefficient of static friction.

	@see setStaticFriction 
	*/
	virtual		PxReal	getStaticFriction() const = 0;

	/**
	\brief Sets the coefficient of restitution 
	
	A coefficient of 0 makes the object bounce as little as possible, higher values up to 1.0 result in more bounce.

	This property is overloaded when PxMaterialFlag::eCOMPLIANT_CONTACT flag is enabled. This permits negative values for restitution to be provided.
	The negative values are converted into spring stiffness terms for an implicit spring simulated at the contact site, with the spring positional error defined by
	the contact separation value. Higher stiffness terms produce stiffer springs that behave more like a rigid contact.

	<b>Sleeping:</b> Does <b>NOT</b> wake any actors which may be affected.

	\param[in] rest Coefficient of restitution. <b>Range:</b> [-INF,1]

	@see getRestitution() 
	*/
	virtual		void	setRestitution(PxReal rest) = 0;

	/**
	\brief Retrieves the coefficient of restitution.     

	See #setRestitution.

	\return The coefficient of restitution.

	@see setRestitution() 
	*/
	virtual		PxReal	getRestitution() const = 0;

	/**
	\brief ���� ����� �����մϴ�.

	�� �Ӽ��� ���� PxMaterialFlag::eCOMPLIANT_CONTACT�� Ȱ��ȭ�Ǿ� ���� �� �ùķ��̼ǿ� ������ ��Ĩ�ϴ�.
	������ ���� ���� ���� ���� ������ ������ ������ �Բ� �۵��մϴ�. ������ ������ ��ġ ������ �����ϰ�,
	������ ��� �ӵ��� �����մϴ�. ���� ���� ����� �����ϸ� ������ ������ ������ ������ �� �ֽ��ϴ�.

	<b>����:</b> ������ ���� �� �ִ� � ���͵� ������ <b>�ʽ��ϴ�.</b>

	\param[in] damping ���� ���. <b>����:</b> [0, ���Ѵ�]

	@see getDamping()
	*/
	virtual		void	setDamping(PxReal damping) = 0;

	/**
	\brief ���� ����� �˻��մϴ�.

	#setDamping�� �����Ͻʽÿ�.

	\return ���� ���.

	@see setDamping()
	*/
	virtual		PxReal	getDamping() const = 0;

	/**
	\brief Ư���� ��Ƽ���� �÷��׸� �����ϰų� �����մϴ�.

	�÷��� ����� #PxMaterialFlag�� �����Ͻʽÿ�.

	<b>�⺻��:</b> eIMPROVED_PATCH_FRICTION

	<b>����:</b> ������ ���� �� �ִ� � ���͵� ������ <b>�ʽ��ϴ�.</b>

	\param[in]	flag ����(�ø���) �Ǵ� ������ PxMaterial �÷����Դϴ�.
	\param[in]	b �÷����� ���ο� ����

	@see getFlags() setFlags() PxMaterialFlag
	*/
	virtual		void	setFlag(PxMaterialFlag::Enum flag, bool b) = 0;

	/**
	\brief ��� ��Ƽ���� �÷��׸� �����մϴ�.

	�÷��� ����� #PxMaterialFlag�� �����Ͻʽÿ�.

	<b>�⺻��:</b> eIMPROVED_PATCH_FRICTION

	<b>����:</b> ������ ���� �� �ִ� � ���͵� ������ <b>�ʽ��ϴ�.</b>

	\param[in]	flags ��� PxMaterial �÷���

	@see getFlags() setFlag() PxMaterialFlag
	*/
	virtual		void 	setFlags(PxMaterialFlags flags) = 0;

	/**
	\brief Retrieves the flags. See #PxMaterialFlag.

	\return The material flags.

	@see PxMaterialFlag setFlags()
	*/
	virtual		PxMaterialFlags	getFlags() const = 0;

	/**
	\brief Sets the friction combine mode.
	
	See the enum ::PxCombineMode .

	<b>Default:</b> PxCombineMode::eAVERAGE

	<b>Sleeping:</b> Does <b>NOT</b> wake any actors which may be affected.

	\param[in] combMode Friction combine mode to set for this material. See #PxCombineMode.

	@see PxCombineMode getFrictionCombineMode setStaticFriction() setDynamicFriction()
	*/
	virtual		void	setFrictionCombineMode(PxCombineMode::Enum combMode) = 0;

	/**
	\brief Retrieves the friction combine mode.
	
	See #setFrictionCombineMode.

	\return The friction combine mode for this material.

	@see PxCombineMode setFrictionCombineMode() 
	*/
	virtual		PxCombineMode::Enum	getFrictionCombineMode() const = 0;

	/**
	\brief Sets the restitution combine mode.
	
	See the enum ::PxCombineMode .

	<b>Default:</b> PxCombineMode::eAVERAGE

	<b>Sleeping:</b> Does <b>NOT</b> wake any actors which may be affected.

	\param[in] combMode Restitution combine mode for this material. See #PxCombineMode.

	@see PxCombineMode getRestitutionCombineMode() setRestitution()
	*/
	virtual		void	setRestitutionCombineMode(PxCombineMode::Enum combMode) = 0;

	/**
	\brief Retrieves the restitution combine mode.
	
	See #setRestitutionCombineMode.

	\return The coefficient of restitution combine mode for this material.

	@see PxCombineMode setRestitutionCombineMode getRestitution()
	*/
	virtual		PxCombineMode::Enum	getRestitutionCombineMode() const = 0;

	// PxBase
	virtual		const char*	getConcreteTypeName() const	PX_OVERRIDE	{ return "PxMaterial"; }
	//~PxBase

protected:
	PX_INLINE			PxMaterial(PxType concreteType, PxBaseFlags baseFlags) : PxBaseMaterial(concreteType, baseFlags)	{}
	PX_INLINE			PxMaterial(PxBaseFlags baseFlags) : PxBaseMaterial(baseFlags) {}
	virtual				~PxMaterial() {}
	virtual		bool	isKindOf(const char* name) const { PX_IS_KIND_OF(name, "PxMaterial", PxBaseMaterial); }
};

#if !PX_DOXYGEN
} // namespace physx
#endif

/** @} */
#endif
