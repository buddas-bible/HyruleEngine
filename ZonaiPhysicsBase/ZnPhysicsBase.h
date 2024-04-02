#pragma once


namespace ZonaiPhysics
{
	class ZnRigidBody;
	class ZnSoftBody;
	class ZnCollider;
	class ZnJoint;


	enum class Shape
	{
		SPHERE,
		BOX,
		CAPSULE,
		PLANE,
		CONVEX,
	};

	class ZnPhysicsBase
	{
	public:
		ZnPhysicsBase() = default;
		virtual ~ZnPhysicsBase();
	
	public:
	/// <summary>
	/// 
	/// </summary>
		virtual void			Initialize() = 0;
		virtual void			Simulation(float _dt) = 0;
		virtual void			Finalize() = 0;

	public:
		/// <summary>
		/// Create Component
		/// </summary>
		virtual ZnRigidBody*	CreateRigidBody() = 0;
		virtual ZnSoftBody*		CreateSoftBody() = 0;
		virtual ZnCollider*		CreateCollider() = 0;
		virtual ZnJoint*		CreateJoint() = 0;
	};
}