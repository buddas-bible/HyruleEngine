#pragma once
#include "Component.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class PlayerController : public Component
	{
	public:
		PlayerController(GameObject*) noexcept;
		virtual ~PlayerController() noexcept = default;

	public:
		float dashSpeed = 1.5f;
		float speed = 1.f;

		void Move(Vector3D);

	public:
		virtual void Awake();
		virtual void Start();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();
	};
}
