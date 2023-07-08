#include "DXInputLayout.h"

#include "DXDevice.h"
#include "DXEffect.h"

namespace Hyrule
{
	DXInputLayout::DXInputLayout(DXDevice* _device, DXEffect* _effect)	: 
		device(_device), effect()
	{

	}

	long DXInputLayout::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC(&desc)[])
	{
		HRESULT hr = S_OK;

		D3DX11_PASS_DESC passDesc;
		effect->GetEffect()->GetPassByIndex(0)->GetDesc(&passDesc);

		device->GetDevice()->CreateInputLayout(
			desc,
			ARRAYSIZE(desc),
			passDesc.pIAInputSignature,				// ���̴� �ڵ� ������
			passDesc.IAInputSignatureSize,			// ���̴� ũ��
			inputLayout.GetAddressOf()
		);

		return 0;
	}

	ID3D11InputLayout* DXInputLayout::GetInputLayout()
	{
		return inputLayout.Get();
	}
}