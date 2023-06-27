#pragma once


namespace Hyrule
{
	class ICollider;
	class IRigidBody;
	class Vector3D;

	class IPFactory
	{
	public:
		IPFactory() noexcept = default;
		virtual ~IPFactory() noexcept = default;

	public:
		virtual ICollider* CreateCollider(
			const Vector3D*& vArr, 
			const size_t vArrSize, 
			const int*& iArr, 
			const size_t iArrSize
		) abstract;

		virtual ICollider* AddCollider();
		virtual void RemoveCollider(ICollider*& _collider) abstract;

		virtual IRigidBody* CreateRigidBody() abstract;
		virtual IRigidBody* AddRigidBody() abstract;
		virtual void RemoveRigidBody() abstract;
	};
}

// 콜라이더, 강체 만들어주고 반환해주는 클래스