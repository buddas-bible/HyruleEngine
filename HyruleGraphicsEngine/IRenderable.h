#pragma once

namespace Hyrule
{
	struct Matrix4x4;

	class IRenderable
	{
	public:
		IRenderable() noexcept = default;
		virtual ~IRenderable() noexcept = default;

	public:
		virtual void SetWorldTransform(const Matrix4x4&) noexcept abstract;

	public:
		// ������Ʈ�� Ȱ��ȭ �Ǿ��°� ��Ȱ��ȭ �Ǿ��°��� �Ǵ��ؼ�
		// ������Ʈ�� �Լ��� ȣ�� ���ϴ� ����.
		virtual void OnDisable() noexcept abstract;
		virtual void OnEnble() noexcept abstract;
	};
}