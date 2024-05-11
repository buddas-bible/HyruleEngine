#include "PlayerController.h"

#include "HEntity.h"
#include "HRigidBody.h"
#include "InputSystem.h"

namespace hyrule
{
	PlayerController::PlayerController(GameObject* _gameObject) :
		Component(_gameObject)
	{

	}

	void hyrule::PlayerController::Awake()
	{

	}

	void hyrule::PlayerController::Start()
	{

	}

	void hyrule::PlayerController::FixedUpdate()
	{

	}

	void hyrule::PlayerController::Update()
	{
		auto& input = InputSystem::GetInstance();

		if (input.KeyDown('W'))
		{
			Move(Vector3D::Forward() * speed);
		}
		if (input.KeyDown('S'))
		{
			Move(Vector3D::Forward() * -speed);
		}
		if (input.KeyDown('A'))
		{
			Move(Vector3D::Right() * -speed);
		}
		if (input.KeyDown('D'))
		{
			Move(Vector3D::Right() * speed);
		}
	}

	void hyrule::PlayerController::LateUpdate()
	{

	}

	void PlayerController::Move(Vector3D _force)
	{
		gameObject->GetComponent<hyrule::RigidBody>()->AddForce(_force);
	}

}