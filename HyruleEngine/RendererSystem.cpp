#include "RendererSystem.h"

#include "IGraphics.h"

namespace Hyrule
{
	void RendererSystem::Render() noexcept
	{
		graphicsEngine->Render();
	}

	void RendererSystem::Finalize() noexcept
	{
		graphicsEngine->Finalize();

		if (graphicsEngine)
		{
			delete graphicsEngine;
		}

		graphicsEngine = nullptr;
	}

	bool RendererSystem::LoadGraphicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		HMODULE graphicsDLL{ LoadLibrary(_path.c_str()) };
		if (graphicsDLL == nullptr)
		{
			MessageBox(_hwnd, L"해당 경로에 Graphics DLL 파일이 존재하지 않습니다.", L"DLL 오류", NULL);
			return false;
		}

		using ImportFunction = IGraphics * (*) ();
		// std::function function{ (ImportFunction)GetProcAddress(graphicsDLL, "CreateRenderer") };
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(graphicsDLL, "CreateRenderer") };

		if (CreateInstance == nullptr)
		{
			MessageBox(_hwnd, L"Graphics DLL에서 함수 포인터를 받아오지 못했습니다.", L"DLL 오류", NULL);
			return false;
		}

		graphicsEngine = CreateInstance();

		if (graphicsEngine == nullptr)
		{
			MessageBox(_hwnd, L"Graphics Engine 객체 생성 실패", L"DLL 오류", NULL);
			return false;
		}

		if (FAILED(graphicsEngine->Initialize((int)_hwnd)))
		{
			return false;
		}

		return true;
	}

	long RendererSystem::OnResize()
	{
		if (!graphicsEngine)
		{
			return S_FALSE;
		}
		auto hr = graphicsEngine->OnResize();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

}