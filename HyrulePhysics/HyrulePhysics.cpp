#include "HyrulePhysics.h"

#include "Collider.h"
#include "RigidBody.h"

namespace Hyrule
{
	namespace Physics
	{
		__declspec(dllexport) IPhysics* CreatePhysics()
		{
			return new Physics::HyrulePhysics;
		}

		__declspec(dllexport) void ReleasePhysics(IPhysics*& _physics)
		{
			if (_physics != nullptr)
			{
				delete _physics;
			}
		}

		ICollider* HyrulePhysics::AddCollider(const std::wstring&)
		{
			// return new Collider();
			return nullptr;
		}


		IRigidBody* HyrulePhysics::AddRigidBody(const std::wstring&)
		{
			return nullptr;
		}

		long HyrulePhysics::Initialize()
		{
			gravity = 9.81f;

			return (long)0L;
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


			return nullptr;
		}


		IRigidBody* HyrulePhysics::CreateRigidBody(const std::wstring& _name)
		{

			return nullptr;
		}

		// 	void HyrulePhysics::SetDetectionType(DetectionType)
		// 	{
		// 
		// 	}
	}
}