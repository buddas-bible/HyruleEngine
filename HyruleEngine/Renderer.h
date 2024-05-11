#pragma once
#include "HComponent.h"

#include "RendererSystem.h"

namespace hyrule
{
	class Mesh;
	class IRenderable;

	class Renderer : public HComponent
	{
	public:
		Renderer() = delete;
		Renderer(HEntity*);
		~Renderer() override = default;

	protected:
		IRenderable* meshData;

	public:
		virtual void PreRender() {};
		virtual void Render() {};
		virtual void PostRender() {};
	};
}

