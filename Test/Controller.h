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

	public:
		virtual void Awake() override;
		virtual void Start() override;
		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

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

