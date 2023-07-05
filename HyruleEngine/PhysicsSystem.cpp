#include "PhysicsSystem.h"

#include "IPhysics.h"

namespace Hyrule
{
	bool PhysicsSystem::LoadPhysicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		HMODULE physicsDLL{ LoadLibrary(_path.c_str()) };
		if (!physicsDLL)
		{
			MessageBox(_hwnd, L"해당 경로에 Physics DLL 파일이 존재하지 않습니다.", L"DLL 오류", MB_OK | MB_ICONWARNING);
			return;
		}
		
		using ImportFunction = Physics::IPhysics* (*) ();
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(physicsDLL, "CreatePhysicsWorld") };
		
		if (!CreateInstance)
		{
			MessageBox(_hwnd, L"Physics DLL에서 함수 포인터를 받아오지 못했습니다.", L"DLL 오류", MB_OK | MB_ICONWARNING);
			return;
		}
		
		if (physicsEngine == nullptr)
		{
			MessageBox(_hwnd, L"Graphics Engine 객체 생성 실패", L"DLL 오류", NULL);
			return;
		}
		
		physicsEngine = CreateInstance();
	}

	void PhysicsSystem::Finalize()
	{
		physicsEngine->Finalize();

		if (physicsEngine)
		{
			delete physicsEngine;
		}

		physicsEngine = nullptr;
	}

	/// <summary>
	/// 충돌 감지
	/// 
	/// 콜라이더 충돌을 체크함
	/// </summary>
	void PhysicsSystem::CollisionDetection()
	{
		physicsEngine->CollisionCheck();
	}

	/// <summary>
	/// 충돌 대응
	/// 
	/// 강체 충돌 시뮬레이션
	/// </summary>
	void PhysicsSystem::CollisionResponse(float _dt)
	{
		physicsEngine->RigidSimulation(_dt);
	}

	Physics::ICollider* PhysicsSystem::AddCollider(const std::wstring& _name, Physics::PHYSICALLYOBJECT_INFO* _info)
	{
		auto collider = physicsEngine->AddCollider(_name, _info);
	}

	Physics::IRigidBody* PhysicsSystem::AddRigidBody(const std::wstring&)
	{

	}

}
