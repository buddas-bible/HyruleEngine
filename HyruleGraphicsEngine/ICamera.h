#pragma once

namespace Hyrule
{
	struct Matrix4x4;
	struct Vector3D;

	class ICamera
	{
	public:
		ICamera() = default;
		virtual ~ICamera() = default;

		virtual void Update(float) abstract;
		virtual  Matrix4x4 GetViewMatrix() const abstract;
		virtual  Matrix4x4 GetProjMatrix() const abstract;
		virtual  Matrix4x4 GetViewProjMatrix() const abstract;

		// 카메라 위치와 보고있는 위치로 카메라 세팅
		virtual  void CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp) abstract;

		// 카메라 위치와 보는 방향으로 카메라 세팅
		virtual  void CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp) abstract;

		// 카메라를 원근 투영으로 세팅
		virtual  void CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far) abstract;

		// 카메라를 직교 투영으로 세팅
		virtual  void CameraOrthographicLH(float _width, float _height, float _near, float _far) abstract;

		virtual  void SetWorldTransform(const Matrix4x4&) noexcept abstract;

		virtual void ZoomIn(float) abstract;
		virtual void ZoomOut(float) abstract;

		virtual  void SetPerspectiveView()abstract;
		virtual  void SetOrthographicView()abstract;
	};
}
