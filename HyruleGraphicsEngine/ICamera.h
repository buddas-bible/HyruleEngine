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

		virtual  void moveWorld(const Vector3D& _move) abstract;	// 월드 방향 이동

		virtual  void moveR(const float& _right) abstract;		// 카메라 시점으로부터 오른쪽으로 이동
		virtual  void moveU(const float& _up)abstract;		// 카메라 시점으로부터 위로 이동
		virtual  void moveL(const float& _look)abstract;		// 카메라 시점으로부터 앞으로 이동

		virtual  void Pitch(const float& _degree)abstract;		// 카메라 위아래 회전
		virtual  void Yaw(const float& _degree)abstract;			// 카메라 좌우 회전
		virtual  void roll(const float _degree)abstract;			// 카메라 시점 시계 반시계 회전

		virtual  void SetPerspectiveView()abstract;
		virtual  void SetOrthographicView()abstract;
	};
}
