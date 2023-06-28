#pragma once
#include "framework.h"

namespace Hyrule
{
	class HyruleEngine;

	class Loop
	{
	public:
		Loop(HINSTANCE _hinstance);
		~Loop() = default;

	public:
		static HyruleEngine* g_engine;

		void Run();

		static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	private:
		HyruleEngine* engine;

		HWND hWnd;
		HINSTANCE hInstance;

		HRESULT Initialize();
		void Finalize();

	private:
		HRESULT SetWindows(HWND& _hwnd, HINSTANCE& hInstance, const std::wstring& _name);
	};
}