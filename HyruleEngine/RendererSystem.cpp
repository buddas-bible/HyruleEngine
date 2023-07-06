#include "RendererSystem.h"

#include "IGraphics.h"

namespace Hyrule
{
	bool RendererSystem::LoadGraphicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		HMODULE graphicsDLL{ LoadLibrary(_path.c_str()) };
		if (graphicsDLL == nullptr)
		{
			MessageBox(_hwnd, L"�ش� ��ο� Graphics DLL ������ �������� �ʽ��ϴ�.", L"DLL ����", NULL);
			return false;
		}

		using ImportFunction = IGraphics * (*) ();
		ImportFunction CreateInstance{ (ImportFunction)GetProcAddress(graphicsDLL, "CreateRenderer") };

		if (CreateInstance == nullptr)
		{
			MessageBox(_hwnd, L"Graphics DLL���� �Լ� �����͸� �޾ƿ��� ���߽��ϴ�.", L"DLL ����", NULL);
			return false;
		}

		graphicsEngine = CreateInstance();

		if (graphicsEngine == nullptr)
		{
			MessageBox(_hwnd, L"Graphics Engine ��ü ���� ����", L"DLL ����", NULL);
			return false;
		}

		if (FAILED(graphicsEngine->Initialize((int)_hwnd)))
		{
			return false;
		}

		return true;
	}

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