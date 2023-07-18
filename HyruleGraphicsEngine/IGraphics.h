#pragma once

namespace Hyrule
{
	class IRenderable;
	struct RENDERABLE_DESC;

	class IGraphics
	{
	public:
		IGraphics() = default;
		virtual ~IGraphics() = default;

	private:


	public:
		virtual long Initialize(int _hwnd) abstract;
		virtual void Update() abstract;
		virtual void Render() abstract;
		virtual void Finalize() abstract;

		virtual long OnResize() abstract;

		virtual IRenderable* GetRenderableObject(RENDERABLE_DESC*) abstract;
	};
}
