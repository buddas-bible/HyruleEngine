#pragma once
#include "Renderer.h"

namespace Hyrule
{
	class Entity;
	class Mesh;

	class CubeRenderer : public Renderer
	{
	public:
		CubeRenderer() = delete;
		CubeRenderer(Entity*);
		~CubeRenderer() override = default;

	public:
		void Render() override;
	};
}
