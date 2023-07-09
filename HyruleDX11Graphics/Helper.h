#pragma once
#include "framework.h"

#include "DXDevice.h"
#include "DXRasterizerState.h"

#include "DXEffect.h"
#include "DXInputLayout.h"
#include "DXMesh.h"

#include "HyruleMath.h"

namespace Hyrule
{
	struct Matrix4x4;

	class Helper
	{
	public:
		Helper(
			std::shared_ptr<DXDevice>,
			std::shared_ptr<DXRasterizerState>,
			std::shared_ptr<DXMesh>
		);
		~Helper() = default;

		void SetViewProjTM(const Matrix4x4&);
		void Render();

	private:
		std::shared_ptr<DXDevice> device;
		std::shared_ptr<DXRasterizerState> rasterState;
		std::shared_ptr<DXMesh> mesh;

		Matrix4x4 viewProjTM;
	};
}
