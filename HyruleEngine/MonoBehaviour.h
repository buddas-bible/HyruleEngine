#pragma once
#include "Behaviour.h"

namespace hyrule
{
	class HCollider;
	class Collision;

	class MonoBehaviour : public Behaviour
	{
	public:
		MonoBehaviour() = delete;
		MonoBehaviour(HEntity* _entity);
		~MonoBehaviour() override = default;

	public:
		virtual void Reset() {};

		virtual void Awake() {};
		virtual void Start() {};

		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

	public:
		virtual void OnTriggerEnter(HCollider*) {};
		virtual void OnTriggerStay(HCollider*) {};
		virtual void OnTriggerExit(HCollider*) {};

		virtual void OnCollisionEnter(Collision*) {};
		virtual void OnCollisionStay(Collision*) {};
		virtual void OnCollisionExit(Collision*) {};

		virtual void OnMouseEnter() {};
		virtual void OnMouseDown() {};
		virtual void OnMouseStay() {};
		virtual void OnMouseUp() {};

		virtual void OnJointBreak() {};

		virtual void OnEnable() {};
		virtual void OnDisable() {};

		virtual void OnDestroy() {};
	};
}