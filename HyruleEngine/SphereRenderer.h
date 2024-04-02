#pragma once
#include "Renderer.h"

namespace Hyrule
{
	class Entity;
	class Mesh;

	class SphereRenderer : public Renderer
	{
	public:
		SphereRenderer() = delete;
		SphereRenderer(Entity*);
		~SphereRenderer() override = default;

	public:
		void Render() override;
	};
}
