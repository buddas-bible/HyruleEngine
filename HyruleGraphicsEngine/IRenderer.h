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
		virtual long Initialize(int _hwnd) abstract;
		virtual void Render() abstract;
		virtual void Finalize() abstract;

		virtual long OnResize() abstract;
	};
}
