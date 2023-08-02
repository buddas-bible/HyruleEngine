#pragma once
#include <string>
#include <vector>


namespace Hyrule
{
	struct Vector2D;
	struct Vector3D;

	namespace Physics
	{
		class ICollider;
		class IRigidBody;
		struct TRANSFORM_INFO;
		struct COLLIDER_INFO;
		struct Manifold;

		class IPhysics
		{
		public:
			IPhysics() noexcept {};
			virtual ~IPhysics() noexcept {};

		public:
			/// <summary>
			/// ������Ʈ �̸�, �ݶ��̴� ������ ����.
			/// </summary>
			virtual ICollider* CreateCollider(const std::wstring&, COLLIDER_INFO*) abstract;
			
			/// <summary>
			/// ������Ʈ �̸��� ����.
			/// </summary>
			virtual IRigidBody* CreateRigidBody(const std::wstring&) abstract;

		public:
			virtual long Initialize() abstract;
			virtual void CollisionDetection() abstract;
			virtual void CollisionResponse(float) abstract;
			virtual void ApplyObjectDestroy() abstract;
			virtual void Finalize() abstract;

			virtual void SetWorldGravity(const Hyrule::Vector3D&) abstract;
		};
	}
}

/*


*/