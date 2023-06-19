#include "HyruleEngine.h"

#include "DX11Graphics.h"
#pragma comment(lib, "HyruleDX11Graphics.lib")


namespace Hyrule
{

	HyruleEngine::HyruleEngine() : isStop(false), renderer(nullptr), physics(nullptr)
	{

	}

	HyruleEngine::~HyruleEngine()
	{

	}

	void HyruleEngine::Initialize()
	{
		renderer = new DX11Graphics;
		if (renderer != nullptr)
		{
			renderer->Initialize();
		}
		if (physics != nullptr)
		{
			// physics->Initialize();
		}
	}

	void HyruleEngine::Finalize()
	{
		if (renderer != nullptr)
		{
			renderer->Finalize();
		}
		if (physics != nullptr)
		{
			// physics->Finalize();
		}
	}

	void HyruleEngine::Update()
	{

	}

	void HyruleEngine::PhysicsUpdate()
	{
		
	}

	void HyruleEngine::Render()
	{

	}

	void HyruleEngine::OnResize()
	{
		renderer->OnResize();
	}

	bool HyruleEngine::IsStop()
	{
		return isStop;
	}
}