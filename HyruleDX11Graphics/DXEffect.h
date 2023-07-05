#pragma once

#include <string>

class ID3DX11Effect;
class ID3DX11EffectTechnique;
class ID3DX11EffectVariable;
class ID3DX11EffectMatrixVariable;
class ID3DX11EffectShaderResourceVariable;

namespace Hyrule
{
	class DXDevice;

	/// <summary>
	/// 이펙트 만들고 들고 있는 친구
	/// </summary>
	class DXEffect
	{
	public:
		DXEffect(DXDevice*);
		~DXEffect();

	private:
		DXDevice* device;

		ID3DX11Effect* effect;

	public:
		long CreateEffect(const std::wstring&);

		ID3DX11Effect* GetEffect();
		void SetRawVariable(ID3DX11EffectVariable**, const std::wstring&);
		void SetMatrixVariable(ID3DX11EffectMatrixVariable**, const std::wstring&);
		void SetMatrixVariable(ID3DX11EffectShaderResourceVariable**, const std::wstring&);
	};
}

