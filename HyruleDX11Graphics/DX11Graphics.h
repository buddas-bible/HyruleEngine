#pragma once
#include "IRenderer.h"

namespace Hyrule
{
	class DX11Graphics : public IRenderer
	{
	public:
		DX11Graphics() = default;
		virtual ~DX11Graphics();

	private:


	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void OnResize() override;
		virtual void Update() override;
		virtual void Render() override;
	};
}