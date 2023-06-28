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
	/// 콜리전 체크
	/// </summary>
	void HyrulePhysics::CollisionCheck()
	{

	}

	/// <summary>
	/// 강체 시뮬레이션
	/// </summary>
	void HyrulePhysics::RigidSimulation(const float _deltaTime)
	{

	}

	/// <summary>
	/// 월드 안에 있는 강체를 전부 삭제함
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