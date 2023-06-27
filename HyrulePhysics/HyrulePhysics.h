#pragma once
#include "IPhysics.h"


namespace Hyrule
{
	class HyrulePhysics : public IPhysics
	{
	public:
		HyrulePhysics() noexcept = delete;
		HyrulePhysics(float) noexcept;
		virtual ~HyrulePhysics() = default;

	public:
		virtual int Initialize() override;
		virtual void CollisionCheck() override;
		virtual void RigidSimulation() override;
		virtual void WorldReset() override;
		virtual void Finalize() override;

	private:
		float gravity;
		// using DetectionType = CollisionDetectionType;
		// DetectionType type;

		void SetGravity(float);
		// void SetDetectionType(DetectionType);
	};
}

/*
���� �������κ��� ������ �и��ϰ� ������

���� ������ ��ü ������Ʈ, �ݶ��̴� ������Ʈ�� ���ؼ� ��� �ؾ��ϳ�..
���� �������� ��ü ������Ʈ�� �߰��Ǹ� ���� ������ ��ü�� ���� ��ȯ �ް� �ϰ�...??


���� ����븸�� ���� UI�� ������ �ڴ�.
���� ���� ����� ������ �׷����� ǥ�ø� �Ѵٵ簡.
�浹 �̺�Ʈ�� �߻��� ��ġ�� ���𰡷� ǥ�ø� �صдٴ���...
*/

/*

*/