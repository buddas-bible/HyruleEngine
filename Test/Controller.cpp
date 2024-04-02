#include "Controller.h"

#include "InputSystem.h"
#include "TimeSystem.h"
#include "Entity.h"
#include "Transform.h"
#include "windows.h"
#include "SceneManager.h"

namespace Hyrule
{
	void Controller::AddControllableObject(int _key, GameObject* _obj)
	{
		controlMap[_key].push_back(_obj);
	}

	void Controller::Awake()
	{

	}

	void Controller::Start()
	{

	}

	void Controller::FixedUpdate()
	{

	}

	void Controller::Update()
	{
		auto& input = InputSystem::GetInstance();
		auto dt = TimeSystem::GetInstance().GetfDeltaTime();

		for (auto& e : controlMap)
		{
			if (input.KeyDownNow(e.first))
			{
				controlObject = e.second;
			}
		}

		if (controlObject.empty())
		{
			return;
		}

		for (auto& e : controlObject)
		{
			if (e == nullptr)
			{
				continue;
			}

			Quaternion currR = e->GetTransform()->GetLocalQuaternion();
			if (input.KeyDown(VK_UP))
			{
				auto q = ToQuaternion(Vector3D::Right(), -5.f * dt);
				currR *= q;
			}
			if (input.KeyDown(VK_DOWN))
			{
				auto q = ToQuaternion(Vector3D::Right(), 5.f * dt);
				currR *= q;
			}
			if (input.KeyDown(VK_LEFT))
			{
				auto q = ToQuaternion(Vector3D::Up(), -5.f * dt);
				currR = q * currR;
			}
			if (input.KeyDown(VK_RIGHT))
			{
				auto q = ToQuaternion(Vector3D::Up(), 5.f * dt);
				currR = q * currR;
			}
			e->GetTransform()->SetLocalQuaternion(currR);

			Matrix4x4 mat = ToMatrix4(currR);
			Vector3D currP = e->GetTransform()->GetLocalPosition();
			if (input.KeyDown('W'))
			{
				currP += mat.Look() * 20.f * dt;
			}
			if (input.KeyDown('S'))
			{
				currP -= mat.Look() * 20.f * dt;
			}
			if (input.KeyDown('D'))
			{
				currP += mat.Right() * 20.f * dt;
			}
			if (input.KeyDown('A'))
			{
				currP -= mat.Right() * 20.f * dt;
			}
			if (input.KeyDown('E'))
			{
				currP += mat.Up() * 20.f * dt;
			}
			if (input.KeyDown('Q'))
			{
				currP -= mat.Up() * 20.f * dt;
			}
			e->GetTransform()->SetLocalPosition(currP);
		}
	}

	void Controller::LateUpdate()
	{

	}

	void Controller::OnEnable()
	{

	}

	void Controller::OnDisable()
	{

	}

	void Controller::OnDestroy()
	{

	}
}
