#include "HyrulePhysics.h"

#include "Collider.h"
#include "RigidBody.h"

namespace Hyrule
{
	IPhysicsWorld* CreatePhysics()
	{
		// return new HyrulePhysics;
		return nullptr;
	}

	void ReleasePhysics(IPhysicsWorld*& _physics)
	{
		if (_physics != nullptr)
		{
			delete _physics;
		}
	}


	HyrulePhysics::HyrulePhysics(float _gravity) noexcept : gravity(_gravity)
	{

	}

	int HyrulePhysics::Initialize()
	{
		return (int)0L;
	}


	ICollider* HyrulePhysics::AddCollider()
	{
		// return new Collider();
	}


	IRigidBody* HyrulePhysics::AddRigidBody()
	{

	}

	/// <summary>
	/// �ݸ��� üũ
	/// </summary>
	void HyrulePhysics::CollisionCheck()
	{

	}

	/// <summary>
	/// ��ü �ùķ��̼�
	/// </summary>
	void HyrulePhysics::RigidSimulation(const float _deltaTime)
	{

	}

	/// <summary>
	/// ���� �ȿ� �ִ� ��ü�� ���� ������
	/// </summary>
	void HyrulePhysics::WorldReset()
	{

	}

	void HyrulePhysics::Finalize()
	{

	}

	void HyrulePhysics::SetGravity(float)
	{

	}


	ICollider* HyrulePhysics::CreateCollider(const std::wstring& _name)
	{
		// auto e = colliderMap[_name];



	}


	IRigidBody* HyrulePhysics::CreateRigidBody(const std::wstring& _name)
	{

	}

// 	void HyrulePhysics::SetDetectionType(DetectionType)
// 	{
// 
// 	}

}