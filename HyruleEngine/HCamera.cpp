#include "HCamera.h"

#include "ICamera.h"
#include "InputSystem.h"
#include <windows.h>
#include "RendererSystem.h"
#include "TimeSystem.h"

#include "HEntity.h"
#include "HTransform.h"


namespace hyrule 
{
	HCamera::HCamera(HEntity* _entity) :
		Renderer(_entity)
	{
		camera = RendererSystem::Instance()->GetCamera();

		Vector3D eye{ 0.0f, 8.f, -9.f };
		Vector3D at{ 0.0f, 6.f, 0.0f };
		entity->GetTransform()->SetLocalPosition(eye);
		entity->GetTransform()->SetLocalQuaternion(RotateVectorToVectorQuaternion(Vector3D::Forward(), (at - eye).Normalized()));
	}

	Matrix4x4 HCamera::GetViewMatrix() const
	{
		return this->camera->GetViewMatrix();
	}

	Matrix4x4 HCamera::GetProjMatrix() const
	{
		return this->camera->GetProjMatrix();
	}

	Matrix4x4 HCamera::GetViewProjMatrix() const
	{
		return this->camera->GetViewProjMatrix();
	}

	void HCamera::CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp)
	{
		this->camera->CameraLookAtLH(_eyePos, _focus, _worldUp);
	}

	void HCamera::CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp)
	{
		this->camera->CameraLookToLH(_eyePos, _direction, _worldUp);
	}

	void HCamera::CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far)
	{
		this->camera->CameraPerspectiveFovLH(_angleY, _ratio, _near, _far);
	}

	void HCamera::CameraOrthographicLH(float _width, float _height, float _near, float _far)
	{
		this->camera->CameraOrthographicLH(_width, _height, _near, _far);
	}

	float HCamera::GetWindowWidth()
	{
		return this->camera->GetWindowWidth();
	}

	float HCamera::GetWindowHeight()
	{
		return this->camera->GetWindowHeight();
	}

	void HCamera::SetPerspectiveView()
	{
		this->camera->SetOrthographicView();
	}

	void HCamera::SetOrthographicView()
	{
		this->camera->SetOrthographicView();
	}

	void HCamera::Update()
	{
		auto dt = TimeSystem::GetInstance().GetfDeltaTime();

		if (InputSystem::Instance().KeyDownNow('Z'))
		{
			camera->ZoomIn(1.f * dt);
		}
		if (InputSystem::Instance().KeyDownNow('X'))
		{
			camera->ZoomOut(1.f * dt);
		}
	}

	void HCamera::LateUpdate()
	{
		if (InputSystem::Instance().KeyDownNow(VK_F7))
		{
			camera->SetPerspectiveView();
		}
		if (InputSystem::Instance().KeyDownNow(VK_F8))
		{
			camera->SetOrthographicView();
		}

		camera->SetWorldTransform(entity->GetTransform()->GetWorldMatrix());
	}
}