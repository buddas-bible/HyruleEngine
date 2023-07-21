#include "DXEffect.h"

#include <fstream>
#include <vector>
#include "DXDevice.h"
#include "HyruleMath.h"

namespace Hyrule
{
	DXEffect::DXEffect(std::shared_ptr<DXDevice> _device, const std::wstring& _path) :
		device(_device), effect()
	{
		auto Device = device.lock();

		std::ifstream fin;

		fin.open(_path.c_str(), std::ios::binary);

		fin.seekg(0, std::ios_base::end);
		int size = (int)fin.tellg();
		fin.seekg(0, std::ios_base::beg);
		std::vector<char> vsCompiledShader(size);

		fin.read(&vsCompiledShader[0], size);
		fin.close();

		long hr = D3DX11CreateEffectFromMemory(
			&vsCompiledShader[0],
			size,
			0,
			Device->GetDevice(),
			&effect
		);

		if (FAILED(hr))
		{
			hr = S_FALSE;
		}
	}

	long DXEffect::CreateEffect()
	{
		HRESULT hr = S_OK;

		if (!effect)
		{
			return S_FALSE;
		}

		tech0 = effect->GetTechniqueByName("Tech");

		worldViewProj = effect->GetVariableByName("worldViewProj")->AsMatrix();
		world = effect->GetVariableByName("world")->AsMatrix();
		worldInvTranspose = effect->GetVariableByName("invTworldViewProj")->AsMatrix();
		// eyePosW = effect->GetVariableByName("eyePosW");
		direction = effect->GetVariableByName("lightDirection");

		return hr;
	}

	ID3DX11Effect* DXEffect::GetEffect()
	{
		return effect.Get();
	}

	ID3DX11EffectTechnique* DXEffect::GetTechnique()
	{
		return tech0.Get();
	}

	void DXEffect::SetWorldViewProj(const Matrix4x4& _mat)
	{
		worldViewProj->SetMatrix(reinterpret_cast<const float*>(&_mat));
	}

	void DXEffect::SetWorld(const Matrix4x4& _mat)
	{
		world->SetMatrix(reinterpret_cast<const float*>(&_mat));
	}

	void DXEffect::SetWorldInvTranspose(const Matrix4x4& _mat)
	{
		worldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&_mat));
	}

	void DXEffect::SetEyePosW(const Vector3D& _vec)
	{
		eyePosW->SetRawValue(&_vec, 0, sizeof(Vector3D));
	}

	void DXEffect::SetDirectionLight(const Vector3D& _vec)
	{
		direction->SetRawValue(&_vec, 0, sizeof(Vector3D));
	}

	std::shared_ptr<DXEffect> Effects::PCEffect{};
	std::shared_ptr<DXEffect> Effects::PUNEffect{};
	std::shared_ptr<DXEffect> Effects::PUNTEffect{};

	void Effects::InitAll(std::shared_ptr<DXDevice> _device)
	{
		PCEffect = std::make_shared<DXEffect>(_device, L"../x64/debug/Color.cso");
		PCEffect->CreateEffect();

		PUNEffect = std::make_shared<DXEffect>(_device, L"../x64/debug/PosNormalColor.cso");
		PUNEffect->CreateEffect();

		// PUNTEffect = std::make_shared<DXEffect>(_device, L"");
		// PUNTEffect->CreateEffect();
	}
}