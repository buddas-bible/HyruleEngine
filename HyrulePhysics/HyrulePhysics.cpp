#include "HyrulePhysics.h"

namespace Hyrule
{
	IPhysics* CreatePhysics()
	{
		return new HyrulePhysics;
	}

	void ReleasePhysics(IPhysics*& _physics)
	{
		if (_physics != nullptr)
		{
			delete _physics;
		}
	}

	int HyrulePhysics::Initialize()
	{
		return (int)0L;
	}

	void HyrulePhysics::FixedUpdate()
	{

	}

	void HyrulePhysics::Update()
	{

	}

	void HyrulePhysics::LastUpdate()
	{

	}

	void HyrulePhysics::Finalize()
	{

	}
}