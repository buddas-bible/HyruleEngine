#include "Loop.h"

#include <cmath>
#include "HyruleEngine.h"
#pragma comment(lib, "HyruleEngine.lib")

namespace Hyrule
{
	HyruleEngine* Loop::g_engine = nullptr;

	Loop::Loop(HINSTANCE hinstance) : 
		m_hInstance(hinstance), m_hWnd(),
		m_engine()
	{

	}

	HRESULT Loop::Initialize()
	{
		HRESULT hr = S_OK;

		hr = SetWindows();
		if (FAILED(hr))
		{
			return hr;
		}

		m_engine = new HyruleEngine;
		if (m_engine == nullptr)
		{
			return S_FALSE;
		}

		g_engine = m_engine;
		hr = m_engine->Initialize((int)m_hWnd);
		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	void Loop::Finalize()
	{
		if (m_engine != nullptr)
		{
			m_engine->Finalize();
			delete m_engine;
		}
	}

	void Loop::Run()
	{
		HRESULT hr = S_OK;
		
		// 윈도우 생성 함수
		hr = Initialize();
		if (FAILED(hr))
		{
			return;
		}

		MSG msg;
	
		while (m_engine->IsStop() == false)
		{
			if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;
				DispatchMessage(&msg);
			}
			else
			{
				// m_engine->Update();
				// m_engine->PhysicsUpdate();
				m_engine->Render();
			}
		}

		Finalize();
	}

	LRESULT CALLBACK Loop::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_ACTIVATE:
			{

			}
			break;

			case WM_SIZE:
			{
				if (g_engine != nullptr)
				{
					g_engine->OnResize();
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

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	HRESULT Loop::SetWindows()
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Hyrule::Loop::WndProc; // 프로시저
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInstance;
		wcex.hIcon = LoadIcon(m_hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = L"KH_Engine";
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);

		m_hWnd = CreateWindowW(
			wcex.lpszClassName,
			L"KH_Engine",
			WS_OVERLAPPEDWINDOW | WS_BORDER | WS_SYSMENU,
			CW_USEDEFAULT,				// 윈도우 좌측 상단의 x 좌표
			CW_USEDEFAULT,				// 윈도우 좌측 상단의 y 좌표
			0,							// 윈도우 가로 방향 해상도
			0,							// 윈도우 세로 방향 해상도
			NULL,
			NULL,
			m_hInstance,
			NULL);

		if (!m_hWnd)
		{
			return S_FALSE;
		}

		float dpi = (float)GetDpiForWindow(m_hWnd);

		SetWindowPos(
			m_hWnd,
			NULL,
			NULL,
			NULL,
			static_cast<int>(ceil(1600.f * dpi / 96.f)),
			static_cast<int>(ceil(900.f * dpi / 96.f)),
			SWP_NOMOVE);

		ShowWindow(m_hWnd, SW_SHOWNORMAL);
		UpdateWindow(m_hWnd);

		return S_OK;
	}
}