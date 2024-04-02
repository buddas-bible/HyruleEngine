#include "PhysicsSystem.h"

#include "IPhysics.h"

namespace Hyrule
{
	bool PhysicsSystem::LoadPhysicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		physicsDLL = LoadLibrary(_path.c_str());
		if (!physicsDLL)
		{
			MessageBox(_hwnd, L"해당 경로에 Physics DLL 파일이 존재하지 않습니다.", L"DLL 오류", MB_OK | MB_ICONWARNING);
			return false;
		}
		
		using ImportFunction = Physics::IPhysics* (*) ();
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(physicsDLL, "CreatePhysics") };
		
		if (CreateInstance == nullptr)
		{
			MessageBox(_hwnd, L"Physics DLL에서 함수 포인터를 받아오지 못했습니다.", L"DLL 오류", MB_OK | MB_ICONWARNING);
			return false;
		}

		physicsEngine = CreateInstance();
		
		if (physicsEngine == nullptr)
		{
			MessageBox(_hwnd, L"Graphics Engine 객체 생성 실패", L"DLL 오류", NULL);
			return false;
		}
		
		if (FAILED(physicsEngine->Initialize()))
		{
			return false;
		}

		return true;
	}

	void PhysicsSystem::Finalize()
	{
		physicsEngine->Finalize();

		if (physicsEngine != nullptr)
		{
			delete physicsEngine;
		}

		physicsEngine = nullptr;

		FreeLibrary(physicsDLL);
	}

	/// <summary>
	/// 충돌 감지
	/// 
	/// 콜라이더 충돌을 체크함
	/// </summary>
	void PhysicsSystem::CollisionDetection()
	{
		physicsEngine->CollisionDetection();
	}


	void PhysicsSystem::ApplyObjectDestroy()
	{
		physicsEngine->ApplyObjectDestroy();
	}

	/// <summary>
	/// 충돌 대응
	/// 
	/// 강체 충돌 시뮬레이션
	/// </summary>
	void PhysicsSystem::CollisionResponse(float _dt)
	{
		physicsEngine->CollisionResponse(_dt);
	}

	Physics::ICollider* PhysicsSystem::CreateCollider(const std::wstring& _name, Physics::COLLIDER_INFO* _info)
	{
		auto collider = physicsEngine->CreateCollider(_name, _info);

		if (!collider)
		{
			return nullptr;
		}

		return collider;
	}

	Physics::IRigidBody* PhysicsSystem::CreateRigidBody(const std::wstring& _name)
	{
		auto rigidbody = physicsEngine->CreateRigidBody(_name);

		if (!rigidbody)
		{
			return nullptr;
		}

		return rigidbody;
	}
}
