#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class Mesh;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer() = delete;
		MeshRenderer(GameObject*) noexcept;
		virtual ~MeshRenderer() noexcept;

	private:
		Mesh* meshData;
	};
}