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
		virtual void Initialize() abstract;
		virtual void Finalize() abstract;
		virtual void OnResize() abstract;
		virtual void Update() abstract;
		virtual void Render() abstract;
	};
}