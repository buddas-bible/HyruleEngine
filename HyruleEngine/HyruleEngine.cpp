#include "HyruleEngine.h"

#include "framework.h"

#include "IRenderer.h"
#pragma comment(lib, "HyruleDX11Graphics.lib")

#include "IPhysicsWorld.h"
#pragma comment(lib, "HyrulePhysics.lib")

namespace Hyrule
{

	HyruleEngine::HyruleEngine() : isStop(false), renderer(nullptr), physics(nullptr)
	{

	}

	HyruleEngine::~HyruleEngine()
	{

	}

	int HyruleEngine::Initialize(int _hwnd)
	{
		HRESULT hr = S_OK;

		renderer = Hyrule::CreateRenderer();

		if (renderer != nullptr)
		{
			hr = renderer->Initialize(_hwnd);

			if (FAILED(hr))
			{
				isStop = true;

				return hr;
			}
		}

		// physics = new IPhysics;

		if (physics != nullptr)
		{
			// physics->Initialize();

			if (FAILED(hr))
			{
				isStop = true;

				return hr;
			}
		}

		return (HRESULT)S_OK;
	}

	void HyruleEngine::Finalize()
	{
		if (renderer != nullptr)
		{
			renderer->Finalize();
			Hyrule::ReleaseRenderer(renderer);
			renderer = nullptr;
		}
		if (physics != nullptr)
		{
			// physics->Finalize();
			// delete physics;
			// physics = nullptr;
		}
	}

	void HyruleEngine::Update()
	{
		// ��ǲ
	}

	void HyruleEngine::PhysicsUpdate()
	{
		// �ݶ��̴� üũ

		// �� ���������� ������Ʈ�� �ݸ��� ���� �̺�Ʈ �Լ��� ������ �Ǿ�� �� ����.

		// ������ٵ� �ùķ��̼�
	}

	void HyruleEngine::Render()
	{
		renderer->Render();
	}

	int HyruleEngine::OnResize()
	{
		HRESULT hr = S_OK;

		hr = renderer->OnResize();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		return (int)hr;
	}

	bool HyruleEngine::IsStop()
	{
		return isStop;
	}
}