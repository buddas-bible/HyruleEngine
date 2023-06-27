#include "HyrulePhysics.h"

namespace Hyrule
{
	IPhysics* CreatePhysics()
	{
		// return new HyrulePhysics;
		return nullptr;
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

	/// <summary>
	/// 콜리전 체크
	/// </summary>
	void HyrulePhysics::CollisionCheck()
	{

	}

	/// <summary>
	/// 강체 시뮬레이션
	/// </summary>
	void HyrulePhysics::RigidSimulation()
	{

	}

	/// <summary>
	/// 월드 안에 있는 강체를 전부 삭제함
	/// </summary>
	void HyrulePhysics::WorldReset()
	{

	}

	void HyrulePhysics::Finalize()
	{

	}

	void HyrulePhysics::SetGravity(float)
	{

	}

// 	void HyrulePhysics::SetDetectionType(DetectionType)
// 	{
// 
// 	}

}