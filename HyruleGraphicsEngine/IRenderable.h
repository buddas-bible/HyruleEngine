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
	};
}