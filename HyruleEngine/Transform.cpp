#include "Transform.h"

#include "GameObject.h"

namespace Hyrule
{
	Transform::Transform(GameObject* _gameObject) noexcept :
		Component(_gameObject), 
		position(), rotation(1.f, 0.f, 0.f, 0.f), scale(1.f, 1.f, 1.f),
		parent(), children()
	{}
	
	Vector3D Transform::GetLocalPosition() noexcept
	{
		return this->position;
	}

	Vector3D Transform::GetWorldPosition() noexcept
	{
		if (parent != nullptr)
		{
			return this->position * parent->GetWorldMatrix();
		}
		else
		{
			return this->position;
		}
	}

	void Transform::SetLocalPosition(const Vector3D& _pos) noexcept
	{
		this->position = _pos;
	}

	Vector3D Transform::GetLocalRotation() noexcept
	{
		return ToEuler(this->rotation);
	}

	Quaternion Transform::GetLocalQuaternion() noexcept
	{
		return this->rotation;
	}

	Quaternion Transform::GetWorldQuaternion() noexcept
	{
		if (parent != nullptr)
		{
			return parent->GetWorldQuaternion() * this->rotation;
		}
		else
		{
			return this->rotation;
		}
	}

	void Transform::SetLocalQuaternion(const Quaternion& _q) noexcept
	{
		this->rotation = _q;
	}

	void Transform::SetLocalRotationFromEuler(const Vector3D& _euler) noexcept
	{
		this->rotation = ToQuaternion(_euler);
	}

	void Transform::SetLocalRotationFromDegree(const Vector3D& _degree) noexcept
	{
		const float radX{ ToRadian(_degree.x) };
		const float radY{ ToRadian(_degree.y) };
		const float radZ{ ToRadian(_degree.z) };
		const float inv2{ 1.f / 2.f };


		Quaternion qx{ std::cos(radX * inv2), std::sin(radX * inv2), 0.f, 0.f };
		Quaternion qy{ std::cos(radY * inv2), 0.f, std::sin(radY * inv2), 0.f };
		Quaternion qz{ std::cos(radZ * inv2), 0.f, 0.f, std::sin(radZ * inv2) };

		rotation = qx * qy * qz;
	}

	Vector3D Transform::GetLocalScale() noexcept
	{
		return this->scale;
	}

	Vector3D Transform::GetWorldScale() noexcept
	{
		if (parent != nullptr)
		{
			auto scl = parent->GetWorldScale();
			return Vector3D(scale.x * scl.x , scale.y * scl.y, scale.z * scl.z);
		}
		else
		{
			return this->scale;
		}
	}

	void Transform::SetLocalScale(const Vector3D& _scl) noexcept
	{
		this->scale = _scl;
	}

	Matrix4x4 Transform::GetParentWorldMatrix() noexcept
	{
		if (parent)
		{
			return parent->GetWorldMatrix();
		}
		else
		{
			return Matrix4x4::Identity();
		}
	}

	Vector3D Transform::GetUp() noexcept
	{
		if (parent != nullptr)
		{
			return Vector3D::Up() * ToMatrix4(parent->GetWorldQuaternion());
		}
		else
		{
			return Vector3D::Up();
		}
	 }
 
	Vector3D Transform::GetForward() noexcept
	{
		if (parent != nullptr)
		{
			return Vector3D::Forward() * ToMatrix4(parent->GetWorldQuaternion());
		}
		else
		{
			return Vector3D::Forward();
		}
	 }

	Vector3D Transform::GetRight() noexcept
	{
		if (parent != nullptr)
		{
			return Vector3D::Right() * ToMatrix4(parent->GetWorldQuaternion());
		}
		else
		{
			return Vector3D::Right();
		}
	 }

	Matrix4x4 Transform::GetLocalMatrix() noexcept
	{
		return ToTransformMatrix(position, rotation, scale);
	}

	Matrix4x4 Transform::GetWorldMatrix() noexcept
	{
		if (parent != nullptr)
		{
			return GetLocalMatrix() * parent->GetWorldMatrix();
		}
		else
		{
			return GetLocalMatrix();
		}
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
		children.push_back(_child);
	}

	void Transform::RemoveChild(Transform* _child) noexcept
	{
		children.erase(remove(children.begin(), children.end(), _child));
	}

	Transform* Transform::GetChild(const size_t _index) noexcept
	{
		if ((_index < 0) || (_index > children.size()))
		{
			return nullptr;
		}

		return children[_index];
	}

	std::vector<Transform*> Transform::Getchildren() noexcept
	{
		return this->children;
	}

	size_t Transform::GetChildCount() noexcept
	{
		return children.size();
	}

	Transform* Transform::FindChild(const std::wstring& _name) noexcept
	{
		for (auto e : children)
		{
			if (e->gameObject->GetName() == _name)
			{
				return e;
			}
		}

		return nullptr;
	}

	void Transform::OnDestroy()
	{
		// 부모관계를 끊음
		if (parent != nullptr)
		{
			parent->RemoveChild(this);
			parent = nullptr;
		}

		// 자식을 전부 파괴함.
		for (auto& e : children)
		{	
			e->gameObject->OnDestroy();
		}
	}
}