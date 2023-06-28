#pragma once


namespace Hyrule
{
	class IPhysicsWorld;
	class ICollider;
	class IRigidBody;
	class Vector3D;

	// enum CollisionDetectionType
	// {
	// 	OBB,
	// 	GJK,
	// };

	class IPFactory
	{
	public:
		IPFactory() noexcept = default;
		virtual ~IPFactory() noexcept = default;

		// class PhsicsWorldSetting
		// {
		// public:
		// 	PhsicsWorldSetting() noexcept = default;
		// 	~PhsicsWorldSetting() noexcept = default;
		// 
		// 
		// public:
		// 	bool useOctree;
		// 	float gravity;
		// };

	public:
		// virtual IPhysics* CreatePhysicsWorld(const PhsicsWorldSetting&) abstract;
	};

	IPFactory* CreatePhysicsFactory();
	void ReleasePhysicsFactory(IPFactory*& _physics);
}