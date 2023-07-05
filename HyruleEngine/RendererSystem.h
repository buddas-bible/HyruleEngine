#pragma once
#include "System.h"

#include "framework.h"
#include <string>


namespace Hyrule
{
	class IGraphics;

	class RendererSystem : public System<RendererSystem>
	{
	public:
		RendererSystem() noexcept = default;
		~RendererSystem() noexcept = default;

	private:
		IGraphics* graphicsEngine;

	public:
		bool LoadGraphicsDLL(const std::wstring&, HWND);

		void Render() noexcept;
		void Finalize() noexcept;
		
		long OnResize();
	};
}

