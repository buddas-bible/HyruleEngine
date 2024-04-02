#pragma once
#include "Behaviour.h"

namespace Hyrule
{
	class Collider;
	class Collision;

	class MonoBehaviour : public Behaviour
	{
	public:
		MonoBehaviour() = delete;
		MonoBehaviour(Entity*);
		~MonoBehaviour() override = default;

	public:
		virtual void Reset() {};

		virtual void Awake() {};
		virtual void Start() {};

		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};

	public:
		virtual void OnTriggerEnter(Collider*) {};
		virtual void OnTriggerStay(Collider*) {};
		virtual void OnTriggerExit(Collider*) {};

		virtual void OnCollisionEnter(Collision*) {};
		virtual void OnCollisionStay(Collision*) {};
		virtual void OnCollisionExit(Collision*) {};

		virtual void OnJointBreak() {};

		virtual void OnEnable() {};
		virtual void OnDisable() {};

		virtual void OnDestroy() {};
	};
}
