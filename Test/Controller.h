#pragma once
#include "Component.h"

#include <map>
#include <vector>

namespace Hyrule
{
	class GameObject;

	class Controller : public Component
	{
	public:
		Controller() noexcept = delete;
		Controller(GameObject*) noexcept;
		virtual ~Controller() noexcept = default;

	private:
		std::map<int, std::vector<GameObject*>> controlMap;
		std::vector<GameObject*> controlObject;



	public:
		void AddControllableObject(int, GameObject*);

		virtual void Awake() override;
		virtual void Start() override;
		virtual void FixedUpdate() override;
		virtual void PrePhysicsUpdate() override {};
		virtual void PhysicsUpdate() override {};
		virtual void LatePhysicsUpdate() override {};
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		// 		virtual void OnTriggerEnter(Collider*) abstract;
		// 		virtual void OnTriggerStay(Collider*) abstract;
		// 		virtual void OnTriggerExit(Collider*) abstract;
		// 
		// 		virtual void OnTriggerEnter() abstract;
		// 		virtual void OnTriggerStay() abstract;
		// 		virtual void OnTriggerExit() abstract;

		virtual void OnCollisionEnter(Collider*) override;
		virtual void OnCollisionStay(Collider*) override;
		virtual void OnCollisionExit(Collider*) override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override;
		virtual void OnCollisionExit() override;

		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void OnDestroy() override;
	};
}

