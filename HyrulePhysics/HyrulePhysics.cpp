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
	/// �ݸ��� üũ
	/// </summary>
	void HyrulePhysics::CollisionCheck()
	{

	}

	/// <summary>
	/// ��ü �ùķ��̼�
	/// </summary>
	void HyrulePhysics::RigidSimulation()
	{

	}

	/// <summary>
	/// ���� �ȿ� �ִ� ��ü�� ���� ������
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