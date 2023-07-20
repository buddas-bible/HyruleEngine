#include "Camera.h"

#include "ICamera.h"
#include "InputSystem.h"
#include <windows.h>
#include "RendererSystem.h"


namespace Hyrule 
{
	Camera::Camera(GameObject* _gameObject) noexcept :
		Component(_gameObject)
	{
		camera = RendererSystem::GetInstance().GetCamera();
	}

	Matrix4x4 Camera::GetViewMatrix() const
	{
		return this->camera->GetViewMatrix();
	}

	Matrix4x4 Camera::GetProjMatrix() const
	{
		return this->camera->GetProjMatrix();
	}

	Matrix4x4 Camera::GetViewProjMatrix() const
	{
		return this->camera->GetViewProjMatrix();
	}

	void Camera::CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp)
	{
		this->camera->CameraLookAtLH(_eyePos, _focus, _worldUp);
	}

	void Camera::CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp)
	{
		this->camera->CameraLookToLH(_eyePos, _direction, _worldUp);
	}

	void Camera::CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far)
	{
		this->camera->CameraPerspectiveFovLH(_angleY, _ratio, _near, _far);
	}

	void Camera::CameraOrthographicLH(float _width, float _height, float _near, float _far)
	{
		this->camera->CameraOrthographicLH(_width, _height, _near, _far);
	}

	void Camera::SetPerspectiveView()
	{
		this->camera->SetOrthographicView();
	}

	void Camera::SetOrthographicView()
	{
		this->camera->SetOrthographicView();
	}

	void Camera::Awake()
	{

	}

	void Camera::LateUpdate()
	{
		auto& input = InputSystem::GetInstance();

		if (input.KeyPress('W'))
			camera->moveL(0.5f);
		if (input.KeyPress('S'))
			camera->moveL(-0.5f);
		if (input.KeyPress('D'))
			camera->moveR(0.5f);
		if (input.KeyPress('A'))
			camera->moveR(-0.5f);
		if (input.KeyPress('E'))
			camera->moveU(0.5f);
		if (input.KeyPress('Q'))
			camera->moveU(-0.5f);

		if (input.KeyPress(VK_UP))
			camera->Pitch(1.f);
		if (input.KeyPress(VK_DOWN))
			camera->Pitch(-1.f);
		if (input.KeyPress(VK_LEFT))
			camera->Yaw(1.f);
		if (input.KeyPress(VK_RIGHT))
			camera->Yaw(-1.f);

	}

	void Camera::OnEnable()
	{

	}

	void Camera::OnDisable()
	{

	}

	void Camera::OnDestroy()
	{

	}
}