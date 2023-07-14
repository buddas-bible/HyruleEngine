#pragma once
#include "System.h"

#include "framework.h"
#include <string>


namespace Hyrule
{
	class IGraphics;
	class IRenderable;

	class RendererSystem : public System<RendererSystem>
	{
	public:
		RendererSystem() noexcept = default;
		~RendererSystem() noexcept = default;
		RendererSystem(const RendererSystem&) = delete;
		void operator=(const RendererSystem&) = delete;

	private:
		IGraphics* graphicsEngine{};
		HMODULE graphicsDLL;

	public:
		bool LoadGraphicsDLL(const std::wstring&, HWND);

		void Update() noexcept;
		void Render() noexcept;
		void DebugRender() noexcept;
		void Finalize() noexcept;
		
		long OnResize();

	public:
		IRenderable* GetRenderableObject();

	};
}

