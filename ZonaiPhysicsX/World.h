#pragma once
#include "ZnPhysicsBase.h"
#include "PxPhysicsAPI.h"
<<<<<<< HEAD
#include <map>
#include <string>

#define PVD_HOST "127.0.0.1"
=======
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe

namespace physx
{
	class PxFoundation;
	class PxPhysics;
	class PxDefaultCpuDispatcher;
	class PxScene;
	class PxMaterial;
	class PxPvd;
	class PxRigidDynamic;
}

namespace ZonaiPhysics
{
	class ZnRigidBody;
	class RigidBody;
	class ZnSoftBody;
	class SoftBody;
	class ZnCollider;
	class Collider;
	class ZnJoint;
	class Joint;
	class ZnTransform;
	class World;

	extern "C"
	{
		__declspec(dllexport) ZnPhysicsBase* CreatePhysics();
	}

	class World : public ZnPhysicsBase
	{
	public:
		World() = default;
		virtual ~World();

	public:
		virtual void			Initialize() override;
		virtual void			Simulation(float _dt) override;
		virtual void			Finalize() override;

	public:
		/// <summary>
		/// Create Component
		/// </summary>
		virtual ZnRigidBody*	CreateRigidBody() override;
		virtual ZnSoftBody*		CreateSoftBody() override;
		virtual ZnCollider*		CreateCollider() override;
		virtual ZnJoint*		CreateJoint() override;


		/// <summary>
		/// Create RigidBoby
		/// </summary>
<<<<<<< HEAD
		virtual ZnRigidBody*	CreateRigidBody(const std::wstring&) override;
=======
		virtual ZnRigidBody*	CreateRigidBody();
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
		
		/// <summary>
		/// Create Collider
		/// </summary>
<<<<<<< HEAD
		virtual ZnCollider*		CreatBoxCollider(const std::wstring&, float width, float height);
		virtual ZnCollider*		CreatPlaneCollider(const std::wstring&);
		virtual ZnCollider*		CreatSphereCollider(const std::wstring&);
		virtual ZnCollider*		CreateCapsuleCollider(const std::wstring&);
		virtual ZnCollider*		CreateCustomCollider(const std::wstring&);
=======
		virtual ZnCollider*		CreatBoxCollider(float width, float height);
		virtual ZnCollider*		CreatPlaneCollider();
		virtual ZnCollider*		CreatSphereCollider();
		virtual ZnCollider*		CreateCapsuleCollider();
		virtual ZnCollider*		CreateCustomCollider();
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
		
		/// <summary>
		/// Create Joint
		/// </summary>
		virtual ZnJoint*		CreatD6Joint(ZnRigidBody*, ZnTransform, ZnRigidBody*, ZnTransform);			// D6 조인트		*사실 뭔지 모름
		virtual ZnJoint*		CreatFixedJoint(ZnRigidBody*, ZnTransform, ZnRigidBody*, ZnTransform);			// 고정 조인트
		virtual ZnJoint*		CreatDistanceJoint(ZnRigidBody*, ZnTransform, ZnRigidBody*, ZnTransform);		// 거리 조인트
		virtual ZnJoint*		CreatSphericalJoint(ZnRigidBody*, ZnTransform, ZnRigidBody*, ZnTransform);		// 구형 조인트
		virtual ZnJoint*		CreatRevoluteJoint(ZnRigidBody*, ZnTransform, ZnRigidBody*, ZnTransform);		// 회전 조인트
		virtual ZnJoint*		CreatPrismaticJoint(ZnRigidBody*, ZnTransform, ZnRigidBody*, ZnTransform);		// 프리즘 조인트
	
	private:
		physx::PxDefaultAllocator		allocator;
		physx::PxDefaultErrorCallback	errorCallback;
		physx::PxFoundation*			foundation;
		physx::PxPhysics*				physics;
		physx::PxDefaultCpuDispatcher*	dispatcher;
		physx::PxScene*					scene;
		physx::PxMaterial*				material;
		physx::PxPvd*					pvd;
<<<<<<< HEAD

	private:
		std::map<std::wstring, RigidBody*> bodies;
		bool first;
=======
>>>>>>> 49329f7c854b5a1bc6f7f78c07b81085dead6dbe
	};
} // namespace ZonaiPhysics

