#pragma once
#include <string>
#include <map>
#include "framework.h"

#include "DXMesh.h"
#include "DXTexture.h"
#include "DXShader.h"
#include "DXDevice.h"

namespace Hyrule
{
	class DXMesh;
	class DXTexture;
	class DXShader;

	class ResourceManager
	{
		ResourceManager() = default;
		~ResourceManager() = default;
	public:
		static ResourceManager& GetInstance();

		void Initialize(std::weak_ptr<DXDevice>);

	public:
		long LoadTexture(const std::wstring& _name, const std::wstring& _path);
		long LoadMesh(const std::wstring& _name, const std::wstring& _path);

		DXMesh* CreateMesh(void* vetArr, UINT _vetWidth, void* idxArr, UINT _idxWidth, UINT _count);
		std::shared_ptr<DXMesh> AddMesh(const std::wstring& _name, void* vetArr, UINT _vetWidth, void* idxArr, UINT _idxWidth, UINT _count);

		void AddTexture(const std::wstring& _name, std::shared_ptr<DXTexture>);
		void AddShader(const std::wstring& _name, std::shared_ptr<DXShader>);

		void RemoveMesh(const std::wstring& _name);
		void RemoveTexture(const std::wstring& _name);
		void RemoveShader(const std::wstring& _name);

		std::shared_ptr<DXMesh> GetMesh(const std::wstring&);
		std::shared_ptr<DXTexture> GetTexture(const std::wstring&);
		std::shared_ptr<DXShader> GetShader(const std::wstring&);

	private:
		using MeshContainer = std::map<std::wstring, std::shared_ptr<DXMesh>>;
		using TextureContainer = std::map<std::wstring, std::shared_ptr<DXTexture>>;
		using ShaderContainer = std::map<std::wstring, std::shared_ptr<DXShader>>;

		std::weak_ptr<DXDevice> device;

		MeshContainer		meshMap;
		TextureContainer	textureMap;
		ShaderContainer		shaderMap;
	};

	class HelerObject
	{
	public:
		static void InitHelperObject();

		static std::shared_ptr<DXMesh> axis;
		static std::shared_ptr<DXMesh> gizmo;

		static std::shared_ptr<DXMesh> box;
		static std::shared_ptr<DXMesh> sphere;
		static std::shared_ptr<DXMesh> plane;
	};
}

