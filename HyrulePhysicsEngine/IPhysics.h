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
		struct RaycastInfo;

		class IPhysics
		{
		public:
			IPhysics() noexcept {};
			virtual ~IPhysics() noexcept {};

		public:
			/// <summary>
			/// 오브젝트 이름, 콜라이더 정보를 받음.
			/// </summary>
			virtual ICollider* CreateCollider(const std::wstring&, COLLIDER_INFO*) abstract;
			
			/// <summary>
			/// 오브젝트 이름을 받음.
			/// </summary>
			virtual IRigidBody* CreateRigidBody(const std::wstring&) abstract;

		public:
			virtual long Initialize() abstract;
			virtual void CollisionDetection() abstract;
			virtual void CollisionResponse(float) abstract;
			virtual void ApplyObjectDestroy() abstract;
			virtual void Finalize() abstract;

			virtual RaycastInfo* Raycast(const Vector3D&, const Vector3D&) abstract;
			virtual RaycastInfo* Raycast(const Vector3D&, const Vector3D&, const float) abstract;

			virtual void SetWorldGravity(const Hyrule::Vector3D&) abstract;
		};
	}
}

/*


*/