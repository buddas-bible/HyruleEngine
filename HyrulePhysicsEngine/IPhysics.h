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

		class IPhysics
		{
		public:
			IPhysics() noexcept {};
			virtual ~IPhysics() noexcept {};

		public:
			/// <summary>
			/// ������Ʈ �̸�, �ݶ��̴� ������ ����.
			/// </summary>
			virtual ICollider* AddCollider(const std::wstring&/*, TRANSFORM_INFO**/, COLLIDER_INFO*) abstract;
			
			/// <summary>
			/// ������Ʈ �̸�, ��ü ������ ����.
			/// </summary>
			virtual IRigidBody* AddRigidBody(const std::wstring&/*, TRANSFORM_INFO**/) abstract;

			virtual void RemoveCollider(const std::wstring&, ICollider*) abstract;
			virtual void RemoveCollider(const std::wstring&, int) abstract;
			virtual void RemoveRigidBody(const std::wstring&) abstract;

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