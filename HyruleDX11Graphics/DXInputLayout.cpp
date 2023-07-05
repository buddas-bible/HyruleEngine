#include "DXInputLayout.h"
#include "framework.h"

#include "DXDevice.h"

namespace Hyrule
{
	int DXInputLayout::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC(&desc)[])
	{
		// D3DX11_PASS_DESC passDesc;
		return 0;
	}

	ID3D11InputLayout* DXInputLayout::GetInputLayout()
	{
		return inputLayout;
	}
}