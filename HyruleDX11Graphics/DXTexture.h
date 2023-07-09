#pragma once
#include "IResource.h"

#include <string>
#include "framework.h"

namespace Hyrule
{
	class DXTexture : public IResource
	{
	public:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;
		Comptr<ID3D11ShaderResourceView> texture;
	};
}