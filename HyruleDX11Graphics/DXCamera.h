#pragma once
#include "ICamera.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class DXCamera : public ICamera
	{
	public:
		DXCamera();

		virtual void Update(float) override;
		virtual  Matrix4x4 GetViewMatrix() const override;
		virtual  Matrix4x4 GetProjMatrix() const override;
		virtual  Matrix4x4 GetViewProjMatrix() const override;

		// 카메라 위치와 보고있는 위치로 카메라 세팅
		virtual  void CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp) override;

		// 카메라 위치와 보는 방향으로 카메라 세팅
		virtual  void CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp) override;

		// 카메라를 원근 투영으로 세팅
		virtual  void CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far) override;

		// 카메라를 직교 투영으로 세팅
		virtual  void CameraOrthographicLH(float _width, float _height, float _near, float _far) override;

		virtual  void moveWorld(const Vector3D& _move) override;	// 월드 방향 이동

		virtual  void moveR(const float& _right) override;		// 카메라 시점으로부터 오른쪽으로 이동
		virtual  void moveU(const float& _up) override;		// 카메라 시점으로부터 위로 이동
		virtual  void moveL(const float& _look) override;		// 카메라 시점으로부터 앞으로 이동

		virtual  void Pitch(const float& _degree) override;		// 카메라 위아래 회전
		virtual  void Yaw(const float& _degree) override;			// 카메라 좌우 회전
		virtual  void roll(const float _degree) override;			// 카메라 시점 시계 반시계 회전

		virtual  void SetPerspectiveView() override;
		virtual  void SetOrthographicView() override;

	private:
		void UpdateLUR();
		void UpdateViewMatrix();

		bool isPerspective{true};

		const Vector3D worldUp{ 0.f, 1.f, 0.f };

		Vector3D m_pos;			// 카메라 위치
		Vector3D m_look;		// 카메라 z
		Vector3D m_up;			// 카메라 y
		Vector3D m_right;		// 카메라 x

		Matrix4x4 m_View;
		Matrix4x4 m_Proj;
		Matrix4x4 m_persProj;
		Matrix4x4 m_orthProj;

		float m_angle;
		float m_ratio;
		float m_height;
		float m_width;
		float m_near;
		float m_far;
	};
}

