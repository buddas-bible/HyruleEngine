#pragma once
#include "Renderer.h"

namespace hyrule
{
	class HEntity;
	class Mesh;

	class SphereRenderer : public Renderer
	{
	public:
		SphereRenderer() = delete;
		SphereRenderer(HEntity* _entity);
		~SphereRenderer() override = default;

	public:
		void Render() override;
	};
}
