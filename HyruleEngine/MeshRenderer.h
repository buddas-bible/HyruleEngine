#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class Mesh;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer() = delete;
		MeshRenderer(GameObject*) noexcept;
		virtual ~MeshRenderer() noexcept;

	private:
		Mesh* meshData;

	public:
		virtual void Awake() override {}
		virtual void OnEnable() override {}
		virtual void Start() override {}
		virtual void FixedUpdate() override {}
		virtual void Update() override {}
		virtual void LastUpdate() override {}
		virtual void Render() override {}

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*) override {}
		virtual void OnCollisionStay(Collider*) override {}
		virtual void OnCollisionExit(Collider*) override {}

		virtual void OnCollisionEnter() override {}
		virtual void OnCollisionStay() override {}
		virtual void OnCollisionExit() override {}

		virtual void OnDestroy() override {};
	};
}