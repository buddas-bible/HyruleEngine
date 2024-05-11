#pragma once
#include "Renderer.h"

namespace hyrule
{
	class HEntity;
	class Mesh;

	class MeshRenderer : public Renderer
	{
	public:
		MeshRenderer() = delete;
		MeshRenderer(HEntity*);
		~MeshRenderer() override = default;

	public:
		void Render() override;
	};
}