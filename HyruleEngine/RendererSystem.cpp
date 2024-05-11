#include "RendererSystem.h"

#include "IGraphics.h"
#include "IRenderable.h"

namespace hyrule
{
	bool RendererSystem::LoadGraphicsDLL(const std::wstring& _path, HWND _hwnd)
	{
		graphicsDLL = LoadLibrary(_path.c_str());
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

	void RendererSystem::Update()
	{
		graphicsEngine->Update();
	}

	void RendererSystem::PreRender()
	{

	}

	void RendererSystem::Render()
	{
		graphicsEngine->Render();
	}

	void RendererSystem::PostRender()
	{

	}

	void RendererSystem::DebugRender()
	{

	}

	void RendererSystem::Finalize()
	{
		graphicsEngine->Finalize();

		if (graphicsEngine != nullptr)
		{
			delete graphicsEngine;
		}

		graphicsEngine = nullptr;

		FreeLibrary(graphicsDLL);
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

	hyrule::ICamera* RendererSystem::GetCamera()
	{
		return graphicsEngine->GetCamera();
	}

	hyrule::IRenderable* RendererSystem::GetRenderableObject(RENDERABLE_DESC* _desc)
	{
		return graphicsEngine->GetRenderableObject(_desc);
	}
}