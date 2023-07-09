#include "RenderableObject.h"


namespace Hyrule
{
	RenderableObject::RenderableObject(std::shared_ptr<DXDevice> _device, std::shared_ptr<DXRasterizerState> _state) :
		device(_device), currState(_state)
	{

	}

	void RenderableObject::SetWorldTM(const Matrix4x4& _world)
	{
		this->worldTM = _world;
	}

	void RenderableObject::Render()
	{

	}
}