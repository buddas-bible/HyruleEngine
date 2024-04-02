#pragma once
#include "Renderer.h"

namespace Hyrule
{
	class Entity;
	class Mesh;

	class MeshRenderer : public Renderer
	{
	public:
		MeshRenderer() = delete;
		MeshRenderer(Entity*);
		~MeshRenderer() override = default;

	public:
		void Render() override;
	};
}