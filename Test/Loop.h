#pragma once
#include "framework.h"

namespace Hyrule
{
	class HyruleEngine;

	class Loop
	{
	public:
		Loop(HINSTANCE hinstance);
		~Loop() = default;

	public:
		static HyruleEngine* g_engine;

		void Run();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		HyruleEngine* m_pEngine;

		HWND m_hWnd;
		HINSTANCE m_hInstance;

		void Initialize();
		void Finalize();

	private:
		bool SetWindows();
	};
}