#include "RenderableObject.h"
#include "DXDevice.h"
#include "DXRasterizerState.h"
#include "DXInputLayout.h"
#include "DXEffect.h"
#include "DXMesh.h"
#include "Vertex.h"

#include "ObjectManager.h"

#include <random>

namespace Hyrule
{
	UINT RenderableObject::id = 0;

	RenderableObject::RenderableObject(
		std::shared_ptr<DXDevice> _device, 
		std::shared_ptr<DXRasterizerState> _state,
		std::shared_ptr<DXMesh> _mesh) noexcept :
		device(_device), currState(_state), mesh(_mesh)
	{
		UID = id;
		id++;
	}


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

	void RenderableObject::OnCollisionEnter() noexcept
	{

	}

	void RenderableObject::OnCollisionStay() noexcept
	{
		m_currRasterizerState = currState->GetWireRasterizerState();
	}

	void RenderableObject::OnCollisionExit() noexcept
	{
		m_currRasterizerState = currState->GetSolidRasterizerState();
	}
#if _DEBUG
#endif

	void RenderableObject::SetViewProjTM(const Matrix4x4& _viewProj) noexcept
	{
		this->viewProjTM = _viewProj;
	}

	void RenderableObject::Render(const Vector3D& eye) noexcept
	{
		device->GetDeviceContext()->RSSetState(m_currRasterizerState.Get());
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

		Matrix4x4 _worldViewProj{ worldTM * viewProjTM };

		Effects::PUNEffect->SetWorld(worldTM);
		Effects::PUNEffect->SetWorldViewProj(_worldViewProj);
		Effects::PUNEffect->SetWorldInvTranspose(worldTM.Inverse().Transpose());
		Effects::PUNEffect->SetEyePosW(eye);
		Effects::PUNEffect->SetLightDirection(Vector3D::Forward());
		Effects::PUNEffect->SetLightPosition(Vector3D(10.f, 10.f, 10.f));
		Effects::PUNEffect->SetLightColor(DXColor::White);

		switch (UID % 4)
		{
			case 0:
				Effects::PUNEffect->SetMeshColor(DXColor::AliceBlue);
				break;
			case 1:
				Effects::PUNEffect->SetMeshColor(DXColor::MediumTurquoise);
				break;
			case 2:
				Effects::PUNEffect->SetMeshColor(DXColor::Blue);
				break;
			case 3:
				Effects::PUNEffect->SetMeshColor(DXColor::IndianRed);
				break;
			default:
				Effects::PUNEffect->SetMeshColor(DXColor::MediumTurquoise);
				break;
		}

		D3DX11_TECHNIQUE_DESC techDesc;
		Effects::PUNEffect->GetTechnique()->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Effects::PUNEffect->GetTechnique()->GetPassByIndex(p)->Apply(0, device->GetDeviceContext());

			device->GetDeviceContext()->DrawIndexed(mesh->indexCount, 0, 0);
		}
	}
}