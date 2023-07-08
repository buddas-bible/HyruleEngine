#include "DXEffect.h"


#include "framework.h"
#include <fstream>
#include <vector>
#include "DXDevice.h"

namespace Hyrule
{
	DXEffect::DXEffect(DXDevice* _device) : 
		device(_device), effect()
	{

	}

	long DXEffect::CreateEffect(const std::wstring& _path)
	{
		HRESULT hr = S_OK;

		std::ifstream fin;

		fin.open(_path.c_str(), std::ios::binary);

		fin.seekg(0, std::ios_base::end);
		int size = (int)fin.tellg();
		fin.seekg(0, std::ios_base::beg);
		std::vector<char> vsCompiledShader(size);

		fin.read(&vsCompiledShader[0], size);
		fin.close();

		hr = D3DX11CreateEffectFromMemory(
			&vsCompiledShader[0],
			size,
			0,
			device->GetDevice(),
			&effect
		);

		return hr;
	}

	ID3DX11Effect* DXEffect::GetEffect()
	{
		return effect.Get();
	}

	void DXEffect::SetTechnique(ID3DX11EffectTechnique** _tech, const std::string& _techName)
	{
		(*_tech) = effect->GetTechniqueByName(_techName.c_str());
	}

	void DXEffect::SetRawVariable(ID3DX11EffectVariable** _value, const std::string& _valueName)
	{
		(*_value) = effect->GetVariableByName(_valueName.c_str());
	}

	void DXEffect::SetMatrixVariable(ID3DX11EffectMatrixVariable** _matrix, const std::string& _valueName)
	{
		(*_matrix) = effect->GetVariableByName(_valueName.c_str())->AsMatrix();
	}

	void DXEffect::SetMatrixVariable(ID3DX11EffectShaderResourceVariable** _resource, const std::string& _valueName)
	{
		(*_resource) = effect->GetVariableByName(_valueName.c_str())->AsShaderResource();
	}
}