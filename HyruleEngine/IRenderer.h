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
		virtual int OnResize() abstract;
		virtual void Update() abstract;
		virtual void Render() abstract;
	};
}