#pragma once


namespace Hyrule
{
	class IRenderer
	{
	public:
		IRenderer() = default;
		virtual ~IRenderer() = default;

	private:


	public:
		virtual int Initialize(int _hwnd) abstract;
		virtual void Finalize() abstract;
		virtual void Render() abstract;
		virtual int OnResize() abstract;
	};

	IRenderer* CreateRenderer();
	void ReleaseRenderer(IRenderer*& _renderer);
}
