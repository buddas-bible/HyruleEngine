#pragma once
#include "Singleton.h"

#include "framework.h"
#include <string>


namespace hyrule
{
	class IGraphics;
	class IRenderable;
	struct RENDERABLE_DESC;
	class ICamera;

	class RendererSystem : public Singleton<RendererSystem>
	{
	private:
		IGraphics* graphicsEngine{};
		HMODULE graphicsDLL;

	public:
		bool LoadGraphicsDLL(const std::wstring&, HWND);

		void Update();
		void PreRender();
		void Render();
		void PostRender();
		void DebugRender();
		void Finalize();
		
		long OnResize();

		ICamera* GetCamera();

	public:
		IRenderable* GetRenderableObject(RENDERABLE_DESC* _desc);

	};
}

