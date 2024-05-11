#pragma once
#include "framework.h"
#include "HyruleMath.h"
#include "IRenderable.h"

namespace hyrule
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
		);
		~RenderableObject() = default;

		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		Comptr<ID3D11RasterizerState2> m_currRasterizerState;

	public:
		void SetTexture(const std::shared_ptr<DXTexture>);
		virtual void SetWorldTransform(const Matrix4x4&) override;
		virtual void OnEnble() override;
		virtual void OnDisable() override;
		// virtual void OnDestory() override;
		virtual bool isActive() override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override; 		
		virtual void OnCollisionExit() override;
#if _DEBUG
#endif

		void SetViewProjTM(const Matrix4x4&);
		void Render(const Vector3D& eye);

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

