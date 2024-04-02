#include "PhysicsSystem.h"

#include "IPhysics.h"

namespace Hyrule
{
	bool PhysicsSystem::LoadPhysicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		physicsDLL = LoadLibrary(_path.c_str());
		if (!physicsDLL)
		{
			MessageBox(_hwnd, L"�ش� ��ο� Physics DLL ������ �������� �ʽ��ϴ�.", L"DLL ����", MB_OK | MB_ICONWARNING);
			return false;
		}
		
		using ImportFunction = Physics::IPhysics* (*) ();
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(physicsDLL, "CreatePhysics") };
		
		if (CreateInstance == nullptr)
		{
			MessageBox(_hwnd, L"Physics DLL���� �Լ� �����͸� �޾ƿ��� ���߽��ϴ�.", L"DLL ����", MB_OK | MB_ICONWARNING);
			return false;
		}

		physicsEngine = CreateInstance();
		
		if (physicsEngine == nullptr)
		{
			MessageBox(_hwnd, L"Graphics Engine ��ü ���� ����", L"DLL ����", NULL);
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
	/// �浹 ����
	/// 
	/// �ݶ��̴� �浹�� üũ��
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
	/// �浹 ����
	/// 
	/// ��ü �浹 �ùķ��̼�
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
