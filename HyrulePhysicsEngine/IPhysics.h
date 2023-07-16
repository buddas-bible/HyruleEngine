#pragma once
#include <string>


namespace Hyrule
{
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
			/// 오브젝트 이름, 콜라이더 정보를 받음.
			/// </summary>
			virtual ICollider* AddCollider(const std::wstring&/*, TRANSFORM_INFO**/, COLLIDER_INFO*) abstract;
			
			/// <summary>
			/// 오브젝트 이름, 강체 정보를 받음.
			/// </summary>
			virtual IRigidBody* AddRigidBody(const std::wstring&/*, TRANSFORM_INFO**/) abstract;

			virtual void RemoveCollider(const std::wstring&, ICollider*) abstract;
			virtual void RemoveCollider(const std::wstring&, int) abstract;
			virtual void RemoveRigidBody(const std::wstring&) abstract;

			virtual std::vector<Manifold*> GetCollisionData() abstract;

		public:
			virtual long Initialize() abstract;
			virtual void CollisionDetection() abstract;
			virtual void CollisionResponse(float) abstract;
			virtual void WorldReset() abstract;
			virtual void Finalize() abstract;

			virtual void SetWorldGravity(const Hyrule::Vector3D&) abstract;
		};
	}
}

/*


*/