#include "Transform.h"

#include "GameObject.h"


namespace Hyrule
{

	Transform::Transform(GameObject* _gameObject) noexcept : 
		Component(_gameObject), 
		parent(), child(), 
		position(), quaternion(), scale()
	{
	
	}

	Transform::~Transform() noexcept
	{
		parent->RemoveChild(this);
		parent = nullptr;

		for (auto& e : child)
		{
			e->RemoveParent();
		}
	}

	Vector3D Transform::GetLocalPosition() noexcept
	{
		return this->position;
	}

	Vector3D Transform::GetLocalRotation() noexcept
	{
		return this->quaternion.ToEuler();
	}

	Quaternion Transform::GetLocalQuaternion() noexcept
	{
		return this->quaternion;
	}

	Quaternion Transform::GetWorldQuaternion() noexcept
	{
		Quaternion q = Quaternion::Identity();

		if (parent != nullptr)
		{
			q = parent->GetWorldQuaternion();
		}

		return q * GetLocalQuaternion();
	}

	Vector3D Transform::GetLocalScale() noexcept
	{
		return this->scale;
	}

	Vector3D Transform::GetUp() noexcept
	{
		Quaternion q = Quaternion::Identity();

		if (parent != nullptr)
		{
			q = parent->GetWorldQuaternion();
		}

		return q * Vector3D{ 0.f, 1.f, 0.f };
	}

	void Transform::SetUp(const Vector3D& _vec) noexcept
	{
		
	}

	Vector3D Transform::GetForward() noexcept
	{
		Quaternion q = Quaternion::Identity();

		if (parent != nullptr)
		{
			q = parent->GetWorldQuaternion();
		}

		return q * Vector3D{ 0.f, 0.f, 1.f };
	}

	void Transform::SetForward(const Vector3D& _vec) noexcept
	{
		// this->quaternion =
	}

	Vector3D Transform::GetRight() noexcept
	{
		Quaternion q = Quaternion::Identity();

		if (parent != nullptr)
		{
			q = parent->GetWorldQuaternion();
		}

		return q * Vector3D{ 1.f, 0.f, 0.f };
	}

	void Transform::SetRight(const Vector3D& _vec) noexcept
	{
		// this->quaternion =
	}

	Matrix4x4 Transform::GetLocalMatrix() noexcept
	{
		return ToTransformMatrix(position, quaternion, scale);
	}

	Matrix4x4 Transform::GetWorldMatrix() noexcept
	{
		Matrix4x4 w = Matrix4x4::Identity();

		if (parent != nullptr)
		{
			w = parent->GetWorldMatrix();
		}

		return GetLocalMatrix() * w;
	}

	Transform* Transform::GetParent() noexcept
	{
		return parent;
	}

	void Transform::SetParent(Transform* _parent) noexcept
	{
		this->parent = _parent;
		this->parent->AddChild(this);
	}

	void Transform::RemoveParent() noexcept
	{
		parent->RemoveChild(this);
		parent = nullptr;
	}

	void Transform::AddChild(Transform* _child) noexcept
	{
		child.push_back(_child);
	}

	void Transform::RemoveChild(Transform* _child) noexcept
	{
		child.erase(remove(child.begin(), child.end(), _child));
	}

	Transform* Transform::GetChild(const int _index) noexcept
	{
		if (_index < 0 || _index > child.size())
		{
			return nullptr;
		}

		return child[_index];
	}

	size_t Transform::GetChildCount() noexcept
	{
		return child.size();
	}

	Transform* Transform::FindChild(const std::wstring& _name) noexcept
	{
		for (auto e : child)
		{
			if (e->gameObject->GetName() == _name)
			{
				return e;
			}
		}

		return nullptr;
	}
}