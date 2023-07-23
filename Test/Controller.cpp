#include "Controller.h"

#include "InputSystem.h"
#include "TimeSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "windows.h"

namespace Hyrule
{
	Controller::Controller(GameObject* _gameObject) noexcept : 
		Component(_gameObject), controlMap()
	{

	}

	void Controller::AddControllableObject(int _key, GameObject* _obj)
	{
		if (_obj == nullptr)
		{
			return;
		}

		controlMap.insert(std::make_pair(_key, _obj));
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
			if (input.KeyPressedNow(e.first))
			{
				controlObject = e.second;
			}
		}

		if (controlObject == nullptr)
		{
			return;
		}

		Quaternion currR = controlObject->GetTransform()->GetLocalQuaternion();
		if (input.KeyPress(VK_UP))
		{
			auto q = ToQuaternion(Vector3D::Right(), -1.f * dt);
			currR *= q;
		}
		if (input.KeyPress(VK_DOWN))
		{
			auto q = ToQuaternion(Vector3D::Right(), 1.f * dt);
			currR *= q;
		}
		if (input.KeyPress(VK_LEFT))
		{
			auto q = ToQuaternion(Vector3D::Up(), -1.f * dt);
			currR *= q;
		}
		if (input.KeyPress(VK_RIGHT))
		{
			auto q = ToQuaternion(Vector3D::Up(), 1.f * dt);
			currR *= q;
		}
		controlObject->GetTransform()->SetLocalQuaternion(currR);

		Matrix4x4 mat = ToMatrix4(currR);
		Vector3D currP = controlObject->GetTransform()->GetLocalPosition();
		if (input.KeyPress('W'))
		{
			currP +=  mat.Look() * 1.f * dt;
		}
		if (input.KeyPress('S'))
		{
			currP -= mat.Look() * 1.f * dt;
		}
		if (input.KeyPress('D'))
		{
			currP += mat.Right() * 1.f * dt;
		}
		if (input.KeyPress('A'))
		{
			currP -= mat.Right() * 1.f * dt;
		}
		if (input.KeyPress('E'))
		{
			currP += mat.Up() * 1.f * dt;
		}
		if (input.KeyPress('Q'))
		{
			currP -= mat.Up() * 10.f * dt;
		}
		controlObject->GetTransform()->SetLocalPosition(currP);
	}

	void Controller::LateUpdate()
	{

	}

	void Controller::Render()
	{

	}

	void Controller::OnCollisionEnter(Collider*)
	{

	}

	void Controller::OnCollisionEnter()
	{

	}

	void Controller::OnCollisionStay(Collider*)
	{

	}

	void Controller::OnCollisionStay()
	{

	}

	void Controller::OnCollisionExit(Collider*)
	{

	}

	void Controller::OnCollisionExit()
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
