#pragma once
#include "framework.h"
#include <string>
#include <vector>

class ID3DX11Effect;
class ID3DX11EffectTechnique;
class ID3DX11EffectVariable;
class ID3DX11EffectMatrixVariable;
class ID3DX11EffectShaderResourceVariable;

namespace Hyrule
{
	class DXDevice;
	struct Matrix4x4;
	struct Vector3D;

	/// <summary>
	/// FX �ڵ� �� �о�� ģ��
	/// FX �ڵ庰�� ������ ������ ���� ������?
	/// ��ũ���̳� ���̾ƿ��� ��
	/// </summary>
	class DXEffect
	{
	public:
		DXEffect(std::shared_ptr<DXDevice>, const std::wstring&);
		~DXEffect() = default;

		DXEffect(const DXEffect&) = delete;
		void operator=(const DXEffect&) = delete;

	private:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;
		std::weak_ptr<DXDevice> device;

		Comptr<ID3DX11Effect> effect;

		Comptr<ID3DX11EffectTechnique> tech0;
		Comptr<ID3DX11EffectMatrixVariable> worldViewProj;
		Comptr<ID3DX11EffectMatrixVariable> world;
		Comptr<ID3DX11EffectMatrixVariable> worldInvTranspose;
		Comptr<ID3DX11EffectVariable> eyePosW;
		Comptr<ID3DX11EffectVariable> direction;

	public:
		long CreateEffect();
		ID3DX11Effect* GetEffect();
		ID3DX11EffectTechnique* GetTechnique();

	public:
		void SetWorldViewProj(const Matrix4x4&);
		void SetWorld(const Matrix4x4&);
		void SetWorldInvTranspose(const Matrix4x4&);
		void SetEyePosW(const Vector3D&);
		void SetDirectionLight(const Vector3D&);
	};

	class Effects
	{
	public:
		static void InitAll(std::shared_ptr<DXDevice>);
	
		static std::shared_ptr<DXEffect> PCEffect;
		static std::shared_ptr<DXEffect> PUNEffect;
		static std::shared_ptr<DXEffect> PUNTEffect;
	};
}

