#pragma once


class ID3D11InputLayout;
class DXDevice;
class DXEffect;
struct D3D11_INPUT_ELEMENT_DESC;

namespace Hyrule
{
	class DXInputLayout
	{
	public:
		DXInputLayout(DXDevice*);
		~DXInputLayout();

	public:
		DXDevice* device;
		DXEffect* effect;

		ID3D11InputLayout* inputLayout;

	public:
		int CreateInputLayout(D3D11_INPUT_ELEMENT_DESC(&)[]);

		ID3D11InputLayout* GetInputLayout();
	};
}