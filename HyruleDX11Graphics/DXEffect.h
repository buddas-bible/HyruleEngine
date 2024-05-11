#pragma once
#include "framework.h"
#include <string>
#include <vector>

class ID3DX11Effect;
class ID3DX11EffectTechnique;
class ID3DX11EffectVariable;
class ID3DX11EffectMatrixVariable;
class ID3DX11EffectShaderResourceVariable;

namespace hyrule
{
	class DXDevice;
	struct Matrix4x4;
	struct Vector3D;
	struct Vector4D;

	/// <summary>
	/// FX 코드 쭉 읽어온 친구
	/// FX 코드별로 가지고 있으면 되지 않을까?
	/// 테크닉이나 레이아웃은 이
	/// </summary>
	class DXEffect
	{
	public:
		DXEffect(std::shared_ptr<DXDevice>, const std::wstring&);
		~DXEffect() = default;

		DXEffect(const DXEffect&) = delete;
		DXEffect& operator=(const DXEffect&) = delete;

	private:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;
		std::weak_ptr<DXDevice> device;

		Comptr<ID3DX11Effect> effect;

		Comptr<ID3DX11EffectTechnique> tech0;
		Comptr<ID3DX11EffectMatrixVariable> world;
		Comptr<ID3DX11EffectMatrixVariable> worldViewProj;
		Comptr<ID3DX11EffectMatrixVariable> worldInvTranspose;

		Comptr<ID3DX11EffectVariable> eyePosW;
		Comptr<ID3DX11EffectVariable> meshColor;

		Comptr<ID3DX11EffectVariable> lightDirection;
		Comptr<ID3DX11EffectVariable> lightPosition;
		Comptr<ID3DX11EffectVariable> lightColor;

	public:
		long CreateEffect();
		ID3DX11Effect* GetEffect();
		ID3DX11EffectTechnique* GetTechnique();

	public:
		void SetWorld(const Matrix4x4&);
		void SetWorldViewProj(const Matrix4x4&);
		void SetWorldInvTranspose(const Matrix4x4&);

		void SetEyePosW(const Vector3D&);
		void SetMeshColor(const Vector4D&);

		void SetLightDirection(const Vector3D&);
		void SetLightPosition(const Vector3D&);
		void SetLightColor(const Vector4D&);
	};


	// class DXHelperEffect : public DXEffect
	// {
	// public:
	// 	DXHelperEffect(std::shared_ptr<DXDevice>, const std::wstring&);
	// 	~DXHelperEffect() = default;
	// 
	// 	DXHelperEffect(const DXHelperEffect&) = delete;
	// 	DXBasicEffect& operator=(const DXHelperEffect&) = delete;
	// 
	// private:
	// 	template <typename T>
	// 	using Comptr = Microsoft::WRL::ComPtr<T>;
	// 	Comptr<ID3DX11EffectTechnique> tech0;
	// 	Comptr<ID3DX11EffectMatrixVariable> worldViewProj;
	// };
	// 
	// 
	// class DXBasicEffect : public DXEffect
	// {
	// public:
	// 	DXBasicEffect(std::shared_ptr<DXDevice>, const std::wstring&);
	// 	~DXBasicEffect() = default;
	// 
	// 	DXBasicEffect(const DXBasicEffect&) = delete;
	// 	DXBasicEffect& operator=(const DXBasicEffect&) = delete;
	// 
	// private:
	// 	template <typename T>
	// 	using Comptr = Microsoft::WRL::ComPtr<T>;
	// 	Comptr<ID3DX11EffectMatrixVariable> worldViewProj;
	// 	Comptr<ID3DX11EffectMatrixVariable> world;
	// 	Comptr<ID3DX11EffectMatrixVariable> worldInvTranspose;
	// };


	class Effects
	{
	public:
		static void InitAll(std::shared_ptr<DXDevice>);
	
		static std::shared_ptr<DXEffect> PCEffect;
		static std::shared_ptr<DXEffect> PUNEffect;
		static std::shared_ptr<DXEffect> PUNTEffect;
	};
}

