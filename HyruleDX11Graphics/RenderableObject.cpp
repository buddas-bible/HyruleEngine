#include "RenderableObject.h"
#include "DXDevice.h"
#include "DXRasterizerState.h"
#include "DXInputLayout.h"
#include "DXEffect.h"
#include "DXMesh.h"
#include "Vertex.h"

#include "ObjectManager.h"

namespace Hyrule
{
	RenderableObject::RenderableObject(
		std::shared_ptr<DXDevice> _device, 
		std::shared_ptr<DXRasterizerState> _state,
		std::shared_ptr<DXMesh> _mesh) noexcept :
		device(_device), currState(_state), mesh(_mesh) {}


	void RenderableObject::SetTexture(const std::shared_ptr<DXTexture> _texture) noexcept
	{
		this->texture = _texture;
	}

	void RenderableObject::SetWorldTransform(const Matrix4x4& _mat) noexcept
	{
		this->worldTM = _mat;
	}

	void RenderableObject::OnEnble() noexcept
	{
		this->activate = true;
	}

	void RenderableObject::OnDisable() noexcept
	{
		this->activate = false;
	}

	bool RenderableObject::isActive() noexcept
	{
		return this->activate;
	}

	// void RenderableObject::OnDestory() noexcept
	// {
	// 
	// }

#if _DEBUG
	void RenderableObject::OnCollisionEnter() noexcept
	{
		currState->SetWireState();
	}

	void RenderableObject::OnCollisionExit() noexcept
	{
		currState->SetSolidState();
	}
#endif

	void RenderableObject::SetViewProjTM(const Matrix4x4& _viewProj) noexcept
	{
		this->viewProjTM = _viewProj;
	}

	void RenderableObject::Render() noexcept
	{
		device->GetDeviceContext()->RSSetState(currState->GetCurrRasterizerState());
		device->GetDeviceContext()->IASetInputLayout(InputLayouts::PUNLayout->GetInputLayout());
		device->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT stride = sizeof(PUN);
		UINT offset = 0;
		device->GetDeviceContext()->IASetVertexBuffers(
			0,
			1,
			mesh->vertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);

		device->GetDeviceContext()->IASetIndexBuffer(
			mesh->indexBuffer.Get(),
			DXGI_FORMAT_R32_UINT,					// 32비트 unsigned int 형으로 읽음
			0
		);

		Matrix4x4 _worldViewProj{ viewProjTM };
		Effects::PUNEffect->SetWorldViewProj(_worldViewProj);

		D3DX11_TECHNIQUE_DESC techDesc;
		Effects::PUNEffect->GetTechnique()->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Effects::PUNEffect->GetTechnique()->GetPassByIndex(p)->Apply(0, device->GetDeviceContext());

			device->GetDeviceContext()->DrawIndexed(mesh->indexCount, 0, 0);
		}
	}
}