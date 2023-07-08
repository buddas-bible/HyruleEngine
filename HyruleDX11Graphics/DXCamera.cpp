#include "DXCamera.h"


namespace Hyrule
{

	DXCamera::DXCamera()
	{
		Vector3D eye{ 0.0f, 8.f, -9.f };
		Vector3D at{ 0.0f, 6.f, 0.0f };
		Vector3D up{ 0.0f, 1.0f, 0.0f };

		this->CameraLookAtLH(eye, at, up);
	}

	void DXCamera::Update(float)
	{

	}

	void DXCamera::UpdateViewMatrix()
	{
		this->m_View = Matrix4x4
		(
			m_right.x, m_up.x, m_look.x, 0.f,
			m_right.y, m_up.y, m_look.y, 0.f,
			m_right.z, m_up.z, m_look.z, 0.f,
			-(m_pos.Dot(m_right)), -(m_pos.Dot(m_up)), -(m_pos.Dot(m_look)), 1.f
		);
	}

	Hyrule::Matrix4x4 DXCamera::GetViewMatrix() const
	{
		return this->m_View;
	}

	Hyrule::Matrix4x4 DXCamera::GetProjMatrix() const
	{
		if (isPerspective)
		{
			return this->m_persProj;
		}
		else
		{
			return this->m_orthProj;
		}
	}

	Hyrule::Matrix4x4 DXCamera::GetViewProjMatrix() const
	{
		return this->GetViewMatrix() * this->GetProjMatrix();
	}

	void DXCamera::CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp)
	{
		Vector3D look = (_focus - _eyePos).Normalize();
		Vector3D right = worldUp.Normalized().Cross(look);
		Vector3D up = look.Cross(right);

		m_look = look;
		m_right = right;
		m_up = up;
		m_pos = _eyePos;

		this->UpdateLUR();
		this->UpdateViewMatrix();
	}

	void DXCamera::CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp)
	{
		Vector3D look = _direction.Normalized();
		Vector3D right = worldUp.Normalized().Cross(look);
		Vector3D up = look.Cross(right);

		m_look = look;
		m_right = right;
		m_up = up;
		m_pos = _eyePos;

		this->UpdateLUR();
		this->UpdateViewMatrix();
	}

	void DXCamera::CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far)
	{
		float nearH = 2.f * _near * std::tanf(_angleY * 0.5f);		// �Ͼ������ �Ÿ� * ź��Ʈ �ݽþ߰� (-1 1�� �ٲ��ֱ� ���� 2����)
		float nearW = nearH * _ratio;						// ȭ�� ������ ���̸� ���ϴϱ� �ʺ� ����
		float scaleX = 2.f * _near / nearW;					// 2 * n / w
		float scaleY = 2.f * _near / nearH;					// 2 * n / h
		float scaleZ = _far / (_far - _near);				// f / f - n
		float translate = -_near * scaleZ;					// - nf / f - n

		m_angle = _angleY;
		m_ratio = _ratio;
		m_near = _near;
		m_far = _far;

		m_persProj = Matrix4x4
		(
			scaleX, 0.f, 0.f, 0.f,
			0.f, scaleY, 0.f, 0.f,
			0.f, 0.f, scaleZ, 1.f,
			0.f, 0.f, translate, 0.f
		);
	}

	void DXCamera::CameraOrthographicLH(float _width, float _height, float _near, float _far)
	{
		float scaleX = 2.f / _width;
		float scaleY = 2.f / _height;
		float scaleZ = 1.f / (_far - _near);
		float translate = -_near * scaleZ;

		m_height = _height;
		m_width = _width;
		m_near = _near;
		m_far = _far;

		m_orthProj = Matrix4x4
		(
			scaleX, 0.f, 0.f, 0.f,
			0.f, scaleY, 0.f, 0.f,
			0.f, 0.f, scaleZ, 0.f,
			0.f, 0.f, translate, 1.f
		);
	}

	void DXCamera::moveWorld(const Vector3D& _move)
	{
		this->m_pos += _move;

		this->UpdateViewMatrix();
	}

	void DXCamera::moveR(const float& _right)
	{
		this->m_right.Normalize();
		this->m_pos += m_right * _right;

		this->UpdateViewMatrix();
	}

	void DXCamera::moveU(const float& _up)
	{
		this->m_up.Normalize();
		this->m_pos += m_up * _up;

		this->UpdateViewMatrix();
	}

	void DXCamera::moveL(const float& _look)
	{
		this->m_look.Normalize();
		this->m_pos += m_look * _look;

		this->UpdateLUR();
		this->UpdateViewMatrix();
	}

	void DXCamera::Pitch(const float& _degree)
	{
		float angle = ToRadian(_degree);

		Matrix3x3 rotate = ToMatrix3(m_right, angle);

		this->m_look = this->m_look.Normalized() * rotate;


		this->UpdateLUR();
		this->UpdateViewMatrix();
	}

	void DXCamera::Yaw(const float& _degree)
	{
		float angle = ToRadian(_degree);

		Matrix3x3 rotate = ToMatrix3(m_up, angle);

		this->m_look = this->m_look.Normalize() * rotate;

		this->UpdateLUR();
		this->UpdateViewMatrix();
	}

	void DXCamera::roll(const float _degree)
	{
		float angle = ToRadian(_degree);

		Matrix3x3 rotate = ToMatrix3(m_look, angle);

		this->m_up = worldUp * rotate;

		this->m_right = m_look.Cross(m_up);
		this->UpdateViewMatrix();
	}

	void DXCamera::SetPerspectiveView()
	{
		this->isPerspective = true;
	}

	void DXCamera::SetOrthographicView()
	{
		this->isPerspective = false;
	}

	void DXCamera::UpdateLUR()
	{
		this->m_look = m_look.Normalize();
		this->m_right = (worldUp.Cross(m_look)).Normalize();
		this->m_up = (m_look.Cross(m_right)).Normalize();
	}
}