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

	}

	void HyrulePhysics::Update()
	{

	}

	void HyrulePhysics::FixedUpdate()
	{

	}

	void HyrulePhysics::Finalize()
	{

	}

}