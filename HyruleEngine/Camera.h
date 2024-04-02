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

		// ī�޶� ��ġ�� �����ִ� ��ġ�� ī�޶� ����
		void CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp);

		// ī�޶� ��ġ�� ���� �������� ī�޶� ����
		void CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp);

		// ī�޶� ���� �������� ����
		void CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far);

		// ī�޶� ���� �������� ����
		void CameraOrthographicLH(float _width, float _height, float _near, float _far);

		void moveWorld(const Vector3D& _move);	// ���� ���� �̵�

		void moveR(const float& _right);		// ī�޶� �������κ��� ���������� �̵�
		void moveU(const float& _up);		// ī�޶� �������κ��� ���� �̵�
		void moveL(const float& _look);		// ī�޶� �������κ��� ������ �̵�

		void Pitch(const float& _degree);		// ī�޶� ���Ʒ� ȸ��
		void Yaw(const float& _degree);			// ī�޶� �¿� ȸ��
		void roll(const float _degree);			// ī�޶� ���� �ð� �ݽð� ȸ��

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

