#pragma once
#include "framework.h"

class ID3D11InputLayout;
struct D3D11_INPUT_ELEMENT_DESC;

namespace Hyrule
{
	class DXDevice;
	class DXEffect;

	class DXInputLayout
	{
	public:
		DXInputLayout() = delete;
		DXInputLayout(DXDevice*, DXEffect*);
		~DXInputLayout() = default;

	public:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		DXDevice* device;
		DXEffect* effect;

		Comptr<ID3D11InputLayout> inputLayout;

	public:
		long CreateInputLayout(D3D11_INPUT_ELEMENT_DESC(&)[]);

		ID3D11InputLayout* GetInputLayout();
	};
}