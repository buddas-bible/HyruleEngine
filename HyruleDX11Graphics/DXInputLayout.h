#pragma once
#include "framework.h"
#include <string>

class ID3D11InputLayout;
class ID3DX11EffectTechnique;
struct D3D11_INPUT_ELEMENT_DESC;

namespace hyrule
{
	struct InputLayoutDesc
	{
		static const D3D11_INPUT_ELEMENT_DESC pc[2];
		static const D3D11_INPUT_ELEMENT_DESC pun[3];
		static const D3D11_INPUT_ELEMENT_DESC punt[4];
	};

	class DXDevice;
	class DXEffect;

	class DXInputLayout
	{
	public:
		DXInputLayout() = delete;
		DXInputLayout(std::shared_ptr<DXDevice>, std::shared_ptr<DXEffect>);
		~DXInputLayout() = default;

	public:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		std::weak_ptr<DXDevice> m_device;
		std::weak_ptr<DXEffect> m_effect;

		Comptr<ID3D11InputLayout> layout;

	public:
		long CreateInputLayout(
			const D3D11_INPUT_ELEMENT_DESC* desc, 
			UINT _descElement
		);

		ID3D11InputLayout* GetInputLayout();
	};

	class InputLayouts
	{
	public:
		static void InitAll(std::shared_ptr<DXDevice> device);

		static std::shared_ptr<DXInputLayout> PCLayout;
		static std::shared_ptr<DXInputLayout> PUNLayout;
		static std::shared_ptr<DXInputLayout> PUNTLayout;
	};
}