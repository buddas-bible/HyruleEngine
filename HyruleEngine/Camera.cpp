#include "Camera.h"

#include "GameObject.h"
#include "Transform.h"

namespace Hyrule 
{
	Camera::Camera(GameObject* _gameObject) noexcept :
		Component(_gameObject), mode(CameraView::PERSPECTIVE),
		angle(), ratio(), height(), width(), near(), far()
	{

	}

	Matrix4x4 Camera::GetViewTM() const noexcept
	{
// 		return this->viewTM;
		return Matrix4x4();
	}

	Matrix4x4 Camera::GetProjTM() const noexcept
	{
// 		if (mode == CameraView::PERSPECTIVE)
// 		{
// 			return this->persProjTM;
// 		}
// 		else
// 		{
// 			return this->orthProjTM;
// 		}
		return Matrix4x4();
	}

	Matrix4x4 Camera::GetViewProjTM() const noexcept
	{
		//		return GetViewTM() * GetProjTM();
		return Matrix4x4();
	}

	void Camera::CreateViewTM() noexcept
	{
//		auto pos = gameObject->GetTransform()->GetLocalPosition();
//
//		viewTM = Matrix4x4
//		{
//			right.x,			up.x,			look.x,				0.f,
//			right.y,			up.y,			look.y,				0.f,
//			right.z,			up.z,			look.z,				0.f,
//			-(pos.Dot(right)),	-(pos.Dot(up)),	-(pos.Dot(look)),	1.f
//		};
	}

	void Camera::CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp)
	{
//		Vector3D L = (_focus - _eyePos).Normalized();
//		Vector3D R = _worldUp.Normalized().Cross(L);
//		Vector3D U = L.Cross(R);
//
//		this->look = L;
//		this->right = R;
//		this->up = U;
//
//		CreateViewTM();
	}

	void Camera::CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp)
	{
//		Vector3D L = _direction.Normalized();
//		Vector3D R = _worldUp.Normalized().Cross(L);
//		Vector3D U = L.Cross(R);
//
//		this->look = L;
//		this->right = R;
//		this->up = U;
//
//		CreateViewTM();
	}

	void Camera::CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far)
	{
//		float nearH = 2.f * _near * tanf(_angleY * 0.5f);	// �Ͼ������ �Ÿ� * ź��Ʈ �ݽþ߰� (-1 1�� �ٲ��ֱ� ���� 2����)
//		float nearW = nearH * _ratio;						// ȭ�� ������ ���̸� ���ϴϱ� �ʺ� ����
//		float scaleX = 2.f * _near / nearW;					// 2 * n / w
//		float scaleY = 2.f * _near / nearH;					// 2 * n / h
//		float scaleZ = _far / (_far - _near);				// f / f - n
//		float translate = -_near * scaleZ;					// - nf / f - n
//
//		angle = _angleY;
//		ratio = _ratio;
//		near = _near;
//		far = _far;
//
//		persProjTM = Matrix4x4
//		(
//			scaleX, 0.f, 0.f, 0.f,
//			0.f, scaleY, 0.f, 0.f,
//			0.f, 0.f, scaleZ, 1.f,
//			0.f, 0.f, translate, 0.f
//		);
	}

	void Camera::CameraOrthographicLH(float _width, float _height, float _near, float _far)
	{
//		float scaleX = 2.f / _width;
//		float scaleY = 2.f / _height;
//		float scaleZ = 1.f / (_far - _near);
//		float translate = -_near * scaleZ;
//
//		height = _height;
//		width = _width;
//		near = _near;
//		far = _far;
//
//		orthProjTM = Matrix4x4
//		(
//			scaleX, 0.f, 0.f, 0.f,
//			0.f, scaleY, 0.f, 0.f,
//			0.f, 0.f, scaleZ, 0.f,
//			0.f, 0.f, translate, 1.f
//		);
	}

	void Camera::MoveX(float _d)
	{
//		auto p = gameObject->GetTransform()->GetLocalPosition();
//		p.x += _d;
//		gameObject->GetTransform()->SetLocalPosition(p);
	}

	void Camera::MoveY(float _d)
	{
//		auto p = gameObject->GetTransform()->GetLocalPosition();
//		p.y += _d;
//		gameObject->GetTransform()->SetLocalPosition(p);
	}

	void Camera::MoveZ(float _d)
	{
//		auto p = gameObject->GetTransform()->GetLocalPosition();
//		p.z += _d;
//		gameObject->GetTransform()->SetLocalPosition(p);
	}

	void Camera::MoveRight(float _d)
	{
//		auto p = gameObject->GetTransform()->GetLocalPosition();
//		p += right * _d;
//		gameObject->GetTransform()->SetLocalPosition(p);
	}

	void Camera::MoveUp(float _d)
	{
//		auto p = gameObject->GetTransform()->GetLocalPosition();
//		p += up * _d;
//		gameObject->GetTransform()->SetLocalPosition(p);
	}

	void Camera::MoveForward(float _d)
	{
//		auto p = gameObject->GetTransform()->GetLocalPosition();
//		p += look * _d;
//		gameObject->GetTransform()->SetLocalPosition(p);
	}

	// ī�޶� �� �Ʒ� ȸ��
	void Camera::Pitch(float _deg)
	{
//		auto rad = ToRadian(_deg);
//
//		auto q = ToQuaternion(right, rad);
//
//		auto curr = gameObject->GetTransform()->GetLocalQuaternion();
//
//		curr *= q;
//
//		gameObject->GetTransform()->SetLocalQuaternion(curr);
//
//		this->look = curr * Vector3D::Forward();
//		this->right = Vector3D::Up().Cross(this->look);
//		this->up = this->look.Cross(this->right);
	}

	// ī�޶� �¿� ȸ��
	void Camera::Yaw(float _deg)
	{
//		auto rad = ToRadian(_deg);
//
//		auto q = ToQuaternion(up, rad);
//
//		auto curr = gameObject->GetTransform()->GetLocalQuaternion();
//
//		curr *= q;
//
//		gameObject->GetTransform()->SetLocalQuaternion(curr);
//
//		this->look = curr * Vector3D::Forward();
//		this->right = Vector3D::Up().Cross(this->look);
//		this->up = this->look.Cross(this->right);
	}

	// ī�޶� ���� �� �������� ȸ��
	void Camera::Roll(float _deg)
	{
//		auto rad = ToRadian(_deg);
//
//		auto q = ToQuaternion(look, rad);
//
//		auto curr = gameObject->GetTransform()->GetLocalQuaternion();
//
//		curr *= q;
//
//		gameObject->GetTransform()->SetLocalQuaternion(curr);
//
//		this->look = curr * Vector3D::Forward();
//		this->right = Vector3D::Up().Cross(this->look);
//		this->up = this->look.Cross(this->right);
	}

	void Camera::SetCameraView(CameraView _mode)
	{
//		this->mode = _mode;
	}

	void Camera::Awake()
	{

	}

	void Camera::Start()
	{

	}

	void Camera::FixedUpdate()
	{

	}

	void Camera::Update()
	{
		// CreateViewTM();
	}

	void Camera::LastUpdate()
	{

	}

	void Camera::Render()
	{

	}

	void Camera::OnCollisionEnter(Collider*)
	{

	}

	void Camera::OnCollisionEnter()
	{

	}

	void Camera::OnCollisionStay(Collider*)
	{

	}

	void Camera::OnCollisionStay()
	{

	}

	void Camera::OnCollisionExit(Collider*)
	{

	}

	void Camera::OnCollisionExit()
	{

	}

	void Camera::OnEnable()
	{

	}

	void Camera::OnDestroy()
	{

	}
}