#include "HyruleEngine.h"

#include "framework.h"
#include "CoreSystem.h"
#include "RendererSystem.h"
#include "PhysicsSystem.h"
#include "TimeSystem.h"

namespace Hyrule
{
	HyruleEngine::HyruleEngine() noexcept : 
		hwnd(), isRunning(true)
	{
		// m_gameEngine = this;
	}

	/// <summary>
	/// �׳� �̱������� ��ü ��ȯ���ִ� �Լ�
	/// </summary>
	/// <returns></returns>
	HyruleEngine& HyruleEngine::GetInstance() noexcept
	{
		static HyruleEngine gameEngine;

		return gameEngine;
	}

	/// <summary>
	/// ���� ���� ����
	/// </summary>
	void HyruleEngine::Run() noexcept
	{
		MSG msg;
		
		TimeSystem::GetInstance().Tick();

		while (isRunning)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				DispatchMessage(&msg);
			}
			else
			{
				isRunning = CoreSystem::GetInstance().GameProcess();
			}
		}
	}

	/// <summary>
	/// �ʱ�ȭ (������ â ����)
	/// </summary>
	void HyruleEngine::Initialize(HINSTANCE hInstance, const std::wstring& _name) noexcept
	{
		// ������ â ����
		this->CreateEngineWindow(hInstance, _name);

		CoreSystem::GetInstance().SetHandle((int)hwnd);
	}

	/// <summary>
	/// �� �Ҵ��� Ǯ���ַ��� ��.
	/// </summary>
	void HyruleEngine::Finalize() noexcept
	{
		// if (rendererEngine != nullptr)
		// {
		// 	// renderer->Finalize();
		// 	rendererEngine = nullptr;
		// }
		// if (physicsEngine != nullptr)
		// {
		// 	// physics->Finalize();
		// 	physicsEngine = nullptr;
		// }
	}

	/// <summary>
	/// ������ â ����
	/// </summary>
	long HyruleEngine::CreateEngineWindow(HINSTANCE& hInstance, const std::wstring& _name) noexcept
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Hyrule::HyruleEngine::WndProc; // ���ν���
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = _name.c_str();
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);

		hwnd = CreateWindowW(
			wcex.lpszClassName,
			_name.c_str(),
			WS_OVERLAPPEDWINDOW | WS_BORDER | WS_SYSMENU,
			CW_USEDEFAULT,				// ������ ���� ����� x ��ǥ
			CW_USEDEFAULT,				// ������ ���� ����� y ��ǥ
			0,							// ������ ���� ���� �ػ�
			0,							// ������ ���� ���� �ػ�
			NULL,
			NULL,
			hInstance,
			NULL);

		if (!hwnd)
		{
			return S_FALSE;
		}

		float dpi = (float)GetDpiForWindow(hwnd);

		SetWindowPos(
			hwnd,
			NULL,
			NULL,
			NULL,
			static_cast<int>(ceil(1600.f * dpi / 96.f)),
			static_cast<int>(ceil(900.f * dpi / 96.f)),
			SWP_NOMOVE);

		ShowWindow(hwnd, SW_SHOWNORMAL);
		UpdateWindow(hwnd);

		return S_OK;
	}

	/// <summary>
	/// â ũ�� �缳��
	/// </summary>
	long HyruleEngine::OnResize() noexcept
	{
		HRESULT hr = S_OK;

		hr = (HRESULT)(RendererSystem::GetInstance().OnResize());

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	/// <summary>
	/// Graphics DLL ���� ��ŷ
	/// </summary>
	void HyruleEngine::LoadGraphicsDLL(const std::wstring& _path) noexcept
	{
		auto& renderer = RendererSystem::GetInstance();

		auto result = renderer.LoadGraphicsDLL(_path, hwnd);
		if (!result)
		{
			isRunning = false;
		}
	}

	/// <summary>
	/// Physics DLL ���� ��ŷ
	/// </summary>
	void HyruleEngine::LoadPhysicsDLL(const std::wstring& _path) noexcept
	{
		auto& physics = PhysicsSystem::GetInstance();

		auto result = physics.LoadPhysicsDLL(_path, hwnd);
		if (!result)
		{
			isRunning = false;
		}
	}

	/// <summary>
	/// ������ �޼��� �Լ�
	/// </summary>
	LRESULT CALLBACK HyruleEngine::WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) noexcept
	{
		switch (_msg)
		{
			case WM_SETFOCUS:
			{
				// �����찡 ��Ŀ�� �� ��
				// Ÿ�� �������� 1.f�� ������ �����Ŵ
				TimeSystem::GetInstance().Start();
			}
 			break;

			case WM_KILLFOCUS:
			{
				// �����찡 ��Ȱ��ȭ �� ��
				// Ÿ�� �������� 0.f�� ������ ������Ŵ
				TimeSystem::GetInstance().Stop();
			}
			break;

			case WM_SIZE:
			{
				if (_wParam == SIZE_MINIMIZED)
				{
					// �����찡 �ּ�ȭ�� ��
					// Ÿ�� �������� 0.f�� ������ ������Ŵ
					TimeSystem::GetInstance().Stop();
				}
				else if (_wParam == SIZE_MAXIMIZED || _wParam == SIZE_RESTORED)
				{
					// �����찡 �ִ�ȭ�� ��
					// ������ ũ�Ⱑ ����� ��
					// if (HyruleEngine::GetInstance() != nullptr)
					// {
						HyruleEngine::GetInstance().OnResize();
					// }
				}
			}
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
			break;
		}

		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
	}
}