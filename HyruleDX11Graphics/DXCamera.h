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

		// ī�޶� ��ġ�� �����ִ� ��ġ�� ī�޶� ����
		virtual  void CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp) override;

		// ī�޶� ��ġ�� ���� �������� ī�޶� ����
		virtual  void CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp) override;

		// ī�޶� ���� �������� ����
		virtual  void CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far) override;

		// ī�޶� ���� �������� ����
		virtual  void CameraOrthographicLH(float _width, float _height, float _near, float _far) override;

		virtual  void moveWorld(const Vector3D& _move) override;	// ���� ���� �̵�

		virtual  void moveR(const float& _right) override;		// ī�޶� �������κ��� ���������� �̵�
		virtual  void moveU(const float& _up) override;		// ī�޶� �������κ��� ���� �̵�
		virtual  void moveL(const float& _look) override;		// ī�޶� �������κ��� ������ �̵�

		virtual  void Pitch(const float& _degree) override;		// ī�޶� ���Ʒ� ȸ��
		virtual  void Yaw(const float& _degree) override;			// ī�޶� �¿� ȸ��
		virtual  void roll(const float _degree) override;			// ī�޶� ���� �ð� �ݽð� ȸ��

		virtual  void SetPerspectiveView() override;
		virtual  void SetOrthographicView() override;

	private:
		void UpdateLUR();
		void UpdateViewMatrix();

		bool isPerspective{true};

		const Vector3D worldUp{ 0.f, 1.f, 0.f };

		Vector3D m_pos;			// ī�޶� ��ġ
		Vector3D m_look;		// ī�޶� z
		Vector3D m_up;			// ī�޶� y
		Vector3D m_right;		// ī�޶� x

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
