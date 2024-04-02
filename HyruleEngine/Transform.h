#pragma once
#include <string>
#include <vector>

#include "HyruleMath.h"
#include "Component.h"

namespace Hyrule
{
	class Entity;

	class Transform : public Component
	{
	public:
		Transform() = delete;
		Transform(Entity*);
		~Transform() override = default;

	private:
		Vector3D position;
		Quaternion rotation;
		Vector3D scale;

	private:
		Hyrule::Transform* parent;
		std::vector<Transform*> children;

	public:
		/// <summary>
		/// 트랜스폼 관련 함수
		/// </summary>
		Vector3D GetLocalPosition();
		Vector3D GetWorldPosition();
		void SetLocalPosition(const Vector3D&);

		Vector3D GetLocalRotation();
		Quaternion GetLocalQuaternion();
		Quaternion GetWorldQuaternion();
		void SetLocalQuaternion(const Quaternion&);
		void SetLocalRotationFromEuler(const Vector3D&);
		void SetLocalRotationFromDegree(const Vector3D&);

		Vector3D GetLocalScale();
		Vector3D GetWorldScale();
		void SetLocalScale(const Vector3D&);

		Matrix4x4 GetParentWorldMatrix();

		Vector3D GetUp();
		Vector3D GetForward();
		Vector3D GetRight();

		Matrix4x4 GetLocalMatrix();
		Matrix4x4 GetWorldMatrix();


	public:
		/// <summary>
		/// 부모자식 관련 함수
		/// </summary>
		Transform* GetParent();
		void SetParent(Transform*);
		void RemoveParent();

		void AddChild(Transform*);
		void RemoveChild(Transform*);

		Transform* GetChild(const size_t);
		std::vector<Transform*> Getchildren();
		size_t GetChildCount();
		Transform* FindChild(const std::wstring&);

	public:
		virtual void OnEnable() final {}
		virtual void OnDisable() final {}
		virtual void OnDestroy() final;
	};
}

