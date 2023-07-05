#include "PhysicsSystem.h"

#include "IPhysics.h"

namespace Hyrule
{
	bool PhysicsSystem::LoadPhysicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		HMODULE physicsDLL{ LoadLibrary(_path.c_str()) };
		if (!physicsDLL)
		{
			MessageBox(_hwnd, L"�ش� ��ο� Physics DLL ������ �������� �ʽ��ϴ�.", L"DLL ����", MB_OK | MB_ICONWARNING);
			return;
		}
		
		using ImportFunction = Physics::IPhysics* (*) ();
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(physicsDLL, "CreatePhysicsWorld") };
		
		if (!CreateInstance)
		{
			MessageBox(_hwnd, L"Physics DLL���� �Լ� �����͸� �޾ƿ��� ���߽��ϴ�.", L"DLL ����", MB_OK | MB_ICONWARNING);
			return;
		}
		
		if (physicsEngine == nullptr)
		{
			MessageBox(_hwnd, L"Graphics Engine ��ü ���� ����", L"DLL ����", NULL);
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
	/// �浹 ����
	/// 
	/// �ݶ��̴� �浹�� üũ��
	/// </summary>
	void PhysicsSystem::CollisionDetection()
	{
		physicsEngine->CollisionCheck();
	}

	/// <summary>
	/// �浹 ����
	/// 
	/// ��ü �浹 �ùķ��̼�
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
