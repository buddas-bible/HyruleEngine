#pragma once
#include "IResource.h"

#include <string>
#include "framework.h"

namespace Hyrule
{
	class DXMesh : public IResource
	{
	public:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;
		Comptr<ID3D11Buffer> vertexBuffer;
		Comptr<ID3D11Buffer> indexBuffer;
		UINT indexCount;
	};
}

