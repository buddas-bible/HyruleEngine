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
		Renderer() = delete;
		Renderer(Entity*);
		~Renderer() override = default;

	protected:
		IRenderable* meshData;

	public:
		virtual void PreRender() {};
		virtual void Render() {};
		virtual void PostRender() {};
	};
}

