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

		// ī�޶� ��ġ�� �����ִ� ��ġ�� ī�޶� ����
		virtual  void CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp) abstract;

		// ī�޶� ��ġ�� ���� �������� ī�޶� ����
		virtual  void CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp) abstract;

		// ī�޶� ���� �������� ����
		virtual  void CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far) abstract;

		// ī�޶� ���� �������� ����
		virtual  void CameraOrthographicLH(float _width, float _height, float _near, float _far) abstract;

		virtual  void moveWorld(const Vector3D& _move) abstract;	// ���� ���� �̵�

		virtual  void moveR(const float& _right) abstract;		// ī�޶� �������κ��� ���������� �̵�
		virtual  void moveU(const float& _up)abstract;		// ī�޶� �������κ��� ���� �̵�
		virtual  void moveL(const float& _look)abstract;		// ī�޶� �������κ��� ������ �̵�

		virtual  void Pitch(const float& _degree)abstract;		// ī�޶� ���Ʒ� ȸ��
		virtual  void Yaw(const float& _degree)abstract;			// ī�޶� �¿� ȸ��
		virtual  void roll(const float _degree)abstract;			// ī�޶� ���� �ð� �ݽð� ȸ��

		virtual  void SetPerspectiveView()abstract;
		virtual  void SetOrthographicView()abstract;
	};
}