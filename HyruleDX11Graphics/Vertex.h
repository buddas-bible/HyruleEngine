#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector2
	{
		constexpr Vector2() noexcept : x(), y() {}
		constexpr Vector2(float _x, float _y) noexcept : x(_x), y(_y) {}
		constexpr Vector2(_In_reads_(2) const float* arr) noexcept : x(arr[0]), y(arr[1]) {}
		constexpr Vector2(const Vector2&) noexcept = default;
		constexpr Vector2(Vector2&&) noexcept = default;
		constexpr Vector2& operator=(const Vector2&) noexcept = default;
		constexpr Vector2& operator=(Vector2&&) noexcept = default;
		float x, y;
	};

	struct Vector3
	{
		constexpr Vector3() noexcept : x(), y(), z() {}
		constexpr Vector3(float _x, float _y, float _z) noexcept : x(_x), y(_y), z(_z) {}
		constexpr Vector3(_In_reads_(3) const float* arr) noexcept : x(arr[0]), y(arr[1]), z(arr[2]) {}
		constexpr Vector3(const Vector3&) noexcept = default;
		constexpr Vector3(Vector3&&) noexcept = default;
		constexpr Vector3& operator=(const Vector3&) noexcept = default;
		constexpr Vector3& operator=(Vector3&&) noexcept = default;
		float x, y, z;
	};

	struct Vector4
	{
		constexpr Vector4() noexcept : x(), y(), z(), w() {}
		constexpr Vector4(float _x, float _y, float _z, float _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
		constexpr Vector4(_In_reads_(4) const float* arr) noexcept : x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {}
		constexpr Vector4(const Vector4&) noexcept = default;
		constexpr Vector4(Vector4&&) noexcept = default;
		constexpr Vector4& operator=(const Vector4&) noexcept = default;
		constexpr Vector4& operator=(Vector4&&) noexcept = default;
		float x, y, z, w;
	};

	struct PC
	{
		Vector3  pos;
		Vector4  color;
	};

	struct PUN
	{
		Vector3 pos;
		Vector2 uv;
		Vector3 normal;
	};

	struct PUNT
	{
		Vector3 pos;
		Vector2 uv;
		Vector3 normal;
		Vector3 tangent;
	};
}