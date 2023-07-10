#include "Helper.h"

#include "Vertex.h"

namespace Hyrule
{
	Helper::Helper(
		std::shared_ptr<DXDevice> _device, 
		std::shared_ptr<DXRasterizerState> _state,
		std::shared_ptr<DXMesh> _mesh) :
		device(_device), rasterState(_state), mesh(_mesh)
	{}

	void Helper::SetViewProjTM(const Matrix4x4& _TM)
	{
		this->viewProjTM = _TM;
	}

	void Helper::Render()
	{
		device->GetDeviceContext()->RSSetState(0);
		device->GetDeviceContext()->IASetInputLayout(InputLayouts::PCLayout->GetInputLayout());
		device->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

		UINT stride = 28;//sizeof(PC);
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
		Effects::PCEffect->SetWorldViewProj(_worldViewProj);

		D3DX11_TECHNIQUE_DESC techDesc;
		Effects::PCEffect->GetTechnique()->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Effects::PCEffect->GetTechnique()->GetPassByIndex(p)->Apply(0, device->GetDeviceContext());

			device->GetDeviceContext()->DrawIndexed(mesh->indexCount, 0, 0);
		}
	}
}