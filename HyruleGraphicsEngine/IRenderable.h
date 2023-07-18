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
		// 오브젝트가 활성화 되었는가 비활성화 되었는가를 판단해서
		// 컴포넌트는 함수만 호출 당하는 느낌.
		virtual void OnDisable() noexcept abstract;
		virtual void OnEnble() noexcept abstract;
	};
}