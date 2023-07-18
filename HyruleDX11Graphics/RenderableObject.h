#pragma once
#include "framework.h"
#include "HyruleMath.h"
#include "IRenderable.h"

namespace Hyrule
{
	class DXDevice;
	class DXRasterizerState;

	class DXMesh;
	class DXTexture;
	class DXShader;

	struct Matrix4x4;

	class RenderableObject : public IRenderable
	{
	public:
		RenderableObject(
			std::shared_ptr<DXDevice>, 
			std::shared_ptr<DXRasterizerState>,
			std::shared_ptr<DXMesh>
		) noexcept;
		~RenderableObject() noexcept = default;

	public:
		void SetTexture(const std::shared_ptr<DXTexture>) noexcept;
		virtual void SetWorldTransform(const Matrix4x4&) noexcept override;
		virtual void OnEnble() noexcept override;
		virtual void OnDisable() noexcept override;

		void SetViewProjTM(const Matrix4x4&) noexcept;
		void Render() noexcept;

	private:
		bool activate{true};

	private:
		std::shared_ptr<DXDevice> device;
		std::shared_ptr<DXRasterizerState> currState;

	private:
		std::shared_ptr<DXMesh> mesh;				// 버텍스 인덱스 정보
		std::shared_ptr<DXTexture> texture;

		Matrix4x4 worldTM;
		Matrix4x4 viewProjTM;
	};
}

