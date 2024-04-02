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
		// 오브젝트가 활성화 되었는가 비활성화 되었는가를 판단해서
		// 컴포넌트는 함수만 호출 당하는 느낌.
		virtual void OnDisable() abstract;
		virtual void OnEnble() abstract;
		virtual bool isActive() abstract;
		
		virtual void OnCollisionEnter() abstract;
		virtual void OnCollisionStay() abstract;
		virtual void OnCollisionExit() abstract;
	};
}