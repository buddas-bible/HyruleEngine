#pragma once
#include "framework.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class DXDevice;
	class DXRasterizerState;

	class DXMesh;
	class DXTexture;
	class DXShader;

	struct Matrix4x4;

	class RenderableObject
	{
	public:
		RenderableObject(
			std::shared_ptr<DXDevice>, 
			std::shared_ptr<DXRasterizerState>
		);
		~RenderableObject() = default;

	public:
		void SetWorldTM(const Matrix4x4&);

		void Render();

	private:
		std::shared_ptr<DXDevice> device;
		std::shared_ptr<DXRasterizerState> currState;

	private:
		std::shared_ptr<DXMesh> mesh;				// 버텍스 인덱스 정보
		std::shared_ptr<DXTexture> texture;

		Matrix4x4 worldTM;
		Matrix4x4 viewTM;
		Matrix4x4 projTM;

	};
}

