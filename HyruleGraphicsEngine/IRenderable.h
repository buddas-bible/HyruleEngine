#pragma once

namespace Hyrule
{
	struct Matrix4x4;

	class IRenderable
	{
	public:
		IRenderable() = default;
		virtual ~IRenderable() = default;

	public:
		virtual void SetWorldTransform(const Matrix4x4&) abstract;

	public:
		// ������Ʈ�� Ȱ��ȭ �Ǿ��°� ��Ȱ��ȭ �Ǿ��°��� �Ǵ��ؼ�
		// ������Ʈ�� �Լ��� ȣ�� ���ϴ� ����.
		virtual void OnDisable() abstract;
		virtual void OnEnble() abstract;
		virtual bool isActive() abstract;
		
		virtual void OnCollisionEnter() abstract;
		virtual void OnCollisionStay() abstract;
		virtual void OnCollisionExit() abstract;
	};
}