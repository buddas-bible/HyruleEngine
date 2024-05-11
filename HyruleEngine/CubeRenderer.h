#pragma once
#include "Renderer.h"

namespace hyrule
{
	class HEntity;
	class Mesh;

	class CubeRenderer : public Renderer
	{
	public:
		CubeRenderer() = delete;
		CubeRenderer(HEntity* _entity);
		~CubeRenderer() override = default;

	public:
		void Render() override;
	};
}
