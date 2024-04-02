#pragma once
#include "MonoBehaviour.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class PlayerController : public MonoBehaviour
	{
	public:
		PlayerController(GameObject*);
		virtual ~PlayerController() = default;

	public:
		float dashSpeed = 1.5f;
		float speed = 1.f;

		void Move(Vector3D);

	public:
		void Awake() override;
		void Start()override;
		void FixedUpdate()override;
		void Update()override;
		void LateUpdate()override;
	};
}
