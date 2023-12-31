#include "Loop.h"

#include <cmath>
#include "HyruleEngine.h"
#pragma comment(lib, "HyruleEngine.lib")

namespace Hyrule
{
	HyruleEngine* Loop::g_engine = nullptr;

	Loop::Loop(HINSTANCE _hinstance) : 
		hInstance(_hinstance), hWnd(),
		engine()
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

		engine = new HyruleEngine;
		if (engine == nullptr)
		{
			return S_FALSE;
		}

		g_engine = engine;
		hr = engine->Initialize((int)hWnd);
		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	void Loop::Finalize()
	{
		if (engine != nullptr)
		{
			engine->Finalize();
			delete engine;
		}
	}

	void Loop::Run()
	{

	}

	HRESULT Loop::SetWindows()
	{
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Hyrule::Loop::WndProc; // 프로시저
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = L"KH_Engine";
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);

		hWnd = CreateWindowW(
			wcex.lpszClassName,
			L"KH_Engine",
			WS_OVERLAPPEDWINDOW | WS_BORDER | WS_SYSMENU,
			CW_USEDEFAULT,				// 윈도우 좌측 상단의 x 좌표
			CW_USEDEFAULT,				// 윈도우 좌측 상단의 y 좌표
			0,							// 윈도우 가로 방향 해상도
			0,							// 윈도우 세로 방향 해상도
			NULL,
			NULL,
			hInstance,
			NULL);

		if (!hWnd)
		{
			return S_FALSE;
		}

		float dpi = (float)GetDpiForWindow(hWnd);

		SetWindowPos(
			hWnd,
			NULL,
			NULL,
			NULL,
			static_cast<int>(ceil(1600.f * dpi / 96.f)),
			static_cast<int>(ceil(900.f * dpi / 96.f)),
			SWP_NOMOVE);

		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);

		return S_OK;
	}
}