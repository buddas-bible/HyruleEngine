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

		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		Comptr<ID3D11RasterizerState2> m_currRasterizerState;

	public:
		void SetTexture(const std::shared_ptr<DXTexture>) noexcept;
		virtual void SetWorldTransform(const Matrix4x4&) noexcept override;
		virtual void OnEnble() noexcept override;
		virtual void OnDisable() noexcept override;
		// virtual void OnDestory() noexcept override;
		virtual bool isActive() noexcept override;

#if _DEBUG
		virtual void OnCollisionEnter() noexcept override;
		virtual void OnCollisionStay() noexcept override; 		
		virtual void OnCollisionExit() noexcept override;
#endif

		void SetViewProjTM(const Matrix4x4&) noexcept;
		void Render() noexcept;

	private:
		static UINT id;
		UINT UID;
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

