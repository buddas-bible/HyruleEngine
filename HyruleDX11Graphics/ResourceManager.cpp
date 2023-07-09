#include "ResourceManager.h"

namespace Hyrule
{

	Hyrule::ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager* insctance = nullptr;

		if (insctance == nullptr)
		{
			insctance = new ResourceManager;
		}
		
		return *insctance;
	}

	void ResourceManager::Initialize(std::weak_ptr<DXDevice> _device)
	{
		this->device = _device;
	}

	long ResourceManager::LoadTexture(const std::wstring& _name, const std::wstring& _path)
	{
		HRESULT hr = S_OK;

		auto _device = device.lock();

		if (_device == nullptr)
		{
			return S_FALSE;
		}

		std::shared_ptr<DXTexture> newtexture;

		// template <typename T>
		// using Comptr = Microsoft::WRL::ComPtr<T>;
		// 
		// Comptr<ID3D11Resource> texture;
		// // Comptr<ID3D11ShaderResourceView> textureView;
		// 
		// hr = DirectX::CreateDDSTextureFromFile(
		// 	_device.Get(),
		// 	_path.c_str(),
		// 	texture.GetAddressOf(), 
		// 	newtexture->texture.GetAddressOf()
		// );

		if (FAILED(hr))
		{
			return hr;
		}

		textureMap[_name] = std::move(newtexture);

		return hr;
	}

	long ResourceManager::LoadMesh(const std::wstring& _name, const std::wstring& _path)
	{
		HRESULT hr = S_OK;

		// �ļ��� ������ �о�� ����
		// ���⼭ ���ؽ�, �ε��� ���� ���·� ����� ����.

		return hr;
	}

	DXMesh* ResourceManager::CreateMesh(void* vetArr, size_t _vetWidth, void* idxArr, size_t _idxWidth, size_t _count)
	{
		HRESULT hr = S_OK;

		auto _device = device.lock();

		if (_device == nullptr)
		{
			return nullptr;
		}

		DXMesh* mesh = new DXMesh;

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = _vetWidth;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vetArr;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		hr = _device->GetDevice()->CreateBuffer(
			&bufferDesc,
			&InitData,
			mesh->vertexBuffer.GetAddressOf()
		);

		if (FAILED(hr))
		{
			return nullptr;
		}

		mesh->indexCount = _count;

		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = _idxWidth;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA indexInit;
		indexInit.pSysMem = idxArr;
		indexInit.SysMemPitch = 0;
		indexInit.SysMemSlicePitch = 0;

		hr = _device->GetDevice()->CreateBuffer(
			&indexBufferDesc,
			&indexInit,
			mesh->indexBuffer.GetAddressOf()
		);

		if (FAILED(hr))
		{
			return nullptr;
		}

		return mesh;
	}

	std::shared_ptr<DXMesh> ResourceManager::AddMesh(const std::wstring& _name, void* vetArr, size_t _vetWidth, void* idxArr, size_t _idxWidth, size_t _count)
	{
		auto mesh = CreateMesh(vetArr, _vetWidth, idxArr, _idxWidth, _count);

		if (!mesh)
		{
			return nullptr;
		}

		std::shared_ptr<DXMesh> temp(mesh);

		meshMap[_name] = temp;

		return meshMap[_name];
	}

	void ResourceManager::AddTexture(const std::wstring& _name, std::shared_ptr<DXTexture> _texture)
	{
		textureMap[_name] = _texture;
	}

	void ResourceManager::AddShader(const std::wstring& _name, std::shared_ptr<DXShader> _shader)
	{
		shaderMap[_name] = _shader;
	}

	void ResourceManager::RemoveMesh(const std::wstring& _name)
	{

	}

	void ResourceManager::RemoveTexture(const std::wstring& _name)
	{

	}

	void ResourceManager::RemoveShader(const std::wstring& _name)
	{

	}

	std::shared_ptr<DXMesh> ResourceManager::GetMesh(const std::wstring& _name)
	{
		auto itr = meshMap.find(_name);

		if (itr == meshMap.end())
		{
			return nullptr;
		}

		return itr->second;
	}

	std::shared_ptr<DXTexture> ResourceManager::GetTexture(const std::wstring& _name)
	{
		auto itr = textureMap.find(_name);

		if (itr == textureMap.end())
		{
			return nullptr;
		}

		return itr->second;
	}

	std::shared_ptr<DXShader> ResourceManager::GetShader(const std::wstring& _name)
	{
		auto itr = shaderMap.find(_name);

		if (itr == shaderMap.end())
		{
			return nullptr;
		}

		return itr->second;
	}
}