#pragma once
#include "Component.h"

#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;
	class Transform;
	class ICamera;

	class Camera : public Renderer
	{
	public:
		Camera() = delete;
		Camera(Entity* _gameObject);
		~Camera() override = default;

	private:
		ICamera* camera;

	public:
		Matrix4x4 GetViewMatrix() const;
		Matrix4x4 GetProjMatrix() const;
		Matrix4x4 GetViewProjMatrix() const;

		// 카메라 위치와 보고있는 위치로 카메라 세팅
		void CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp);

		// 카메라 위치와 보는 방향으로 카메라 세팅
		void CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp);

		// 카메라를 원근 투영으로 세팅
		void CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far);

		// 카메라를 직교 투영으로 세팅
		void CameraOrthographicLH(float _width, float _height, float _near, float _far);

		void moveWorld(const Vector3D& _move);	// 월드 방향 이동

		void moveR(const float& _right);		// 카메라 시점으로부터 오른쪽으로 이동
		void moveU(const float& _up);		// 카메라 시점으로부터 위로 이동
		void moveL(const float& _look);		// 카메라 시점으로부터 앞으로 이동

		void Pitch(const float& _degree);		// 카메라 위아래 회전
		void Yaw(const float& _degree);			// 카메라 좌우 회전
		void roll(const float _degree);			// 카메라 시점 시계 반시계 회전

		float GetWindowWidth();
		float GetWindowHeight();

		void SetPerspectiveView();
		void SetOrthographicView();

	/// <summary>
	/// component
	/// </summary>
	public:
		void Update() override;
		void LateUpdate() override;
	};
}

