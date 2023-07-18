#include "DXInputLayout.h"

#include "DXDevice.h"
#include "DXEffect.h"

namespace Hyrule
{
	const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::pc[2] = {
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 12,	D3D11_INPUT_PER_VERTEX_DATA,	0 }
	};


	const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::pun[3] = {
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 20,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};

	const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::punt[4] = {
			{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 20,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
			{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 32,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};

	DXInputLayout::DXInputLayout(std::shared_ptr<DXDevice> _device, std::shared_ptr<DXEffect> _effect)	:
		m_device(_device), m_effect(_effect)
	{}

	long DXInputLayout::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* desc, UINT _descElement)
	{
		HRESULT hr = S_OK;

		auto effect = m_effect.lock();

		if (effect == nullptr)
		{
			return S_FALSE;
		}

		D3DX11_PASS_DESC passDesc;
		hr = effect->GetTechnique()->GetPassByIndex(0)->GetDesc(&passDesc);

		if (FAILED(hr))
		{
			return hr;
		}

		auto device = m_device.lock();

		if (device == nullptr)
		{
			return S_FALSE;
		}

		hr = device->GetDevice()->CreateInputLayout(
			desc,
			_descElement,
			passDesc.pIAInputSignature,		// 셰이더 코드 포인터
			passDesc.IAInputSignatureSize,					// 셰이더 크기
			layout.GetAddressOf()
		);

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	ID3D11InputLayout* DXInputLayout::GetInputLayout()
	{
		return layout.Get();
	}

	std::shared_ptr<DXInputLayout> InputLayouts::PCLayout{};
	std::shared_ptr<DXInputLayout> InputLayouts::PUNLayout{};
	std::shared_ptr<DXInputLayout> InputLayouts::PUNTLayout{};

	void InputLayouts::InitAll(std::shared_ptr<DXDevice> device)
	{
		PCLayout = std::make_shared<DXInputLayout>(device, Effects::PCEffect);
		PCLayout->CreateInputLayout(InputLayoutDesc::pc, ARRAYSIZE(InputLayoutDesc::pc));

		PUNLayout = std::make_shared<DXInputLayout>(device, Effects::PUNEffect);
		PUNLayout->CreateInputLayout(InputLayoutDesc::pun, ARRAYSIZE(InputLayoutDesc::pun));

		// PUNTLayout = std::make_shared<DXInputLayout>(device, Effects::PUNTEffect);
		// PUNTLayout->CreateInputLayout(&InputLayoutDesc::punt[0], sizeof(InputLayoutDesc::punt));
	}
}