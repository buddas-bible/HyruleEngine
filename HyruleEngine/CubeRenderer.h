#pragma once
#include "Renderer.h"

namespace Hyrule
{
	class GameObject;
	class Mesh;

	class CubeRenderer : public Renderer
	{
	public:
		CubeRenderer() = delete;
		CubeRenderer(GameObject*) noexcept;
		virtual ~CubeRenderer() noexcept = default;

	public:
		// virtual void FixedUpdate() override;
		virtual void Update() override;
		// virtual void LastUpdate() override;
		// virtual void Render() override;

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;
	};
}
