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