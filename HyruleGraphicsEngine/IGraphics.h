#pragma once

namespace Hyrule
{
	class IGraphics
	{
	public:
		IGraphics() = default;
		virtual ~IGraphics() = default;

	private:


	public:
		virtual long Initialize(int _hwnd) abstract;
		virtual void Render() abstract;
		virtual void Finalize() abstract;

		virtual long OnResize() abstract;
	};
}
