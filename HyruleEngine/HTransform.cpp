#include "HTransform.h"

#include "HEntity.h"

namespace hyrule
{
	HTransform::HTransform(HEntity* _entity) :
		HComponent(_entity), 
		position(), rotation(1.f, 0.f, 0.f, 0.f), scale(1.f, 1.f, 1.f),
		parent(), children()
	{}
	
	Vector3D HTransform::GetLocalPosition()
	{
		return position;
	}

	Vector3D HTransform::GetWorldPosition()
	{
		if (parent != nullptr)
		{
			return position * parent->GetWorldMatrix();
		}
		else
		{
			return position;
		}
	}

	void HTransform::SetLocalPosition(const Vector3D& _pos)
	{
		position = _pos;
	}

	Vector3D HTransform::GetLocalRotation()
	{
		return ToEuler(rotation);
	}

	Quaternion HTransform::GetLocalQuaternion()
	{
		return rotation;
	}

	Quaternion HTransform::GetWorldQuaternion()
	{
		if (parent != nullptr)
		{
			return parent->GetWorldQuaternion() * rotation;
		}
		else
		{
			return rotation;
		}
	}

	void HTransform::SetLocalQuaternion(const Quaternion& _q)
	{
		rotation = _q;
	}

	void HTransform::SetLocalRotationFromEuler(const Vector3D& _euler)
	{
		rotation = ToQuaternion(_euler);
	}

	void HTransform::SetLocalRotationFromDegree(const Vector3D& _degree)
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

	Vector3D HTransform::GetLocalScale()
	{
		return scale;
	}

	Vector3D HTransform::GetWorldScale()
	{
		if (parent != nullptr)
		{
			auto scl = parent->GetWorldScale();
			return Vector3D(scale.x * scl.x , scale.y * scl.y, scale.z * scl.z);
		}
		else
		{
			return scale;
		}
	}

	void HTransform::SetLocalScale(const Vector3D& _scl)
	{
		scale = _scl;
	}

	Matrix4x4 HTransform::GetParentWorldMatrix()
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

	Vector3D HTransform::GetUp()
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
 
	Vector3D HTransform::GetForward()
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

	Vector3D HTransform::GetRight()
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

	Matrix4x4 HTransform::GetLocalMatrix()
	{
		return ToTransformMatrix(position, rotation, scale);
	}

	Matrix4x4 HTransform::GetWorldMatrix()
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

	HTransform* HTransform::GetParent()
	{
		return parent;
	}

	void HTransform::SetParent(HTransform* _parent)
	{
		parent = _parent;
		parent->AddChild(this);
	}

	void HTransform::RemoveParent()
	{
		parent->RemoveChild(this);
		parent = nullptr;
	}

	void HTransform::AddChild(HTransform* _child)
	{
		children.push_back(_child);
	}

	void HTransform::RemoveChild(HTransform* _child)
	{
		children.erase(remove(children.begin(), children.end(), _child));
	}

	HTransform* HTransform::GetChild(const size_t _index)
	{
		if ((_index < 0) || (_index > children.size()))
		{
			return nullptr;
		}

		return children[_index];
	}

	std::vector<HTransform*> HTransform::Getchildren()
	{
		return this->children;
	}

	size_t HTransform::GetChildCount()
	{
		return children.size();
	}

	HTransform* HTransform::FindChild(const std::string& _name)
	{
		for (auto e : children)
		{
			if (e->entity->GetName() == _name)
			{
				return e;
			}
		}

		return nullptr;
	}

	HTransform* HTransform::FindChild(const InstanceID& _id)
	{
		for (auto e : children)
		{
			if (e->entity->GetInstanceID() == _id)
			{
				return e;
			}
		}

		return nullptr;
	}

	void HTransform::OnDestroy()
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
			e->entity->OnDestroy();
		}
	}
}