#include "Transform.h"

#include "Entity.h"

namespace Hyrule
{
	Transform::Transform(Entity* _gameObject) :
		Component(_gameObject), 
		position(), rotation(1.f, 0.f, 0.f, 0.f), scale(1.f, 1.f, 1.f),
		parent(), children()
	{}
	
	Vector3D Transform::GetLocalPosition()
	{
		return this->position;
	}

	Vector3D Transform::GetWorldPosition()
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

	void Transform::SetLocalPosition(const Vector3D& _pos)
	{
		this->position = _pos;
	}

	Vector3D Transform::GetLocalRotation()
	{
		return ToEuler(this->rotation);
	}

	Quaternion Transform::GetLocalQuaternion()
	{
		return this->rotation;
	}

	Quaternion Transform::GetWorldQuaternion()
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

	void Transform::SetLocalQuaternion(const Quaternion& _q)
	{
		this->rotation = _q;
	}

	void Transform::SetLocalRotationFromEuler(const Vector3D& _euler)
	{
		this->rotation = ToQuaternion(_euler);
	}

	void Transform::SetLocalRotationFromDegree(const Vector3D& _degree)
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

	Vector3D Transform::GetLocalScale()
	{
		return this->scale;
	}

	Vector3D Transform::GetWorldScale()
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

	void Transform::SetLocalScale(const Vector3D& _scl)
	{
		this->scale = _scl;
	}

	Matrix4x4 Transform::GetParentWorldMatrix()
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

	Vector3D Transform::GetUp()
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
 
	Vector3D Transform::GetForward()
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

	Vector3D Transform::GetRight()
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

	Matrix4x4 Transform::GetLocalMatrix()
	{
		return ToTransformMatrix(position, rotation, scale);
	}

	Matrix4x4 Transform::GetWorldMatrix()
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

	Transform* Transform::GetParent()
	{
		return parent;
	}

	void Transform::SetParent(Transform* _parent)
	{
		this->parent = _parent;
		this->parent->AddChild(this);
	}

	void Transform::RemoveParent()
	{
		parent->RemoveChild(this);
		parent = nullptr;
	}

	void Transform::AddChild(Transform* _child)
	{
		children.push_back(_child);
	}

	void Transform::RemoveChild(Transform* _child)
	{
		children.erase(remove(children.begin(), children.end(), _child));
	}

	Transform* Transform::GetChild(const size_t _index)
	{
		if ((_index < 0) || (_index > children.size()))
		{
			return nullptr;
		}

		return children[_index];
	}

	std::vector<Transform*> Transform::Getchildren()
	{
		return this->children;
	}

	size_t Transform::GetChildCount()
	{
		return children.size();
	}

	Transform* Transform::FindChild(const std::wstring& _name)
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