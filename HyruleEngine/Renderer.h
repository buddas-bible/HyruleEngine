#pragma once
#include "Component.h"

#include "RendererSystem.h"

namespace Hyrule
{
	class Mesh;
	class IRenderable;

	class Renderer : public Component
	{
	public:
		Renderer() noexcept = delete;
		Renderer(GameObject*) noexcept;
		virtual ~Renderer() noexcept = default;

	protected:
		IRenderable* meshData;

	public:
		virtual void Awake() final {};
		virtual void OnEnable() final;
		virtual void OnDisable() final;
		virtual void Start() final {};
		virtual void FixedUpdate() final {};
		virtual void Update() abstract;
		virtual void LateUpdate() final {};
		virtual void Render() final {};

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*) final {};
		virtual void OnCollisionStay(Collider*) final {};
		virtual void OnCollisionExit(Collider*) final {};

		virtual void OnCollisionEnter() final {};
		virtual void OnCollisionStay() final {};
		virtual void OnCollisionExit() final {};

		virtual void OnDestroy() final {};
	};
}

