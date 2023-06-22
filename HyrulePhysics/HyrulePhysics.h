#pragma once
#include "IPhysics.h"


namespace Hyrule
{
	class HyrulePhysics : public IPhysics
	{
	public:
		HyrulePhysics() = default;
		virtual ~HyrulePhysics() = default;

	public:
		virtual int Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Finalize() override;

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