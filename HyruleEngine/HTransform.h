#pragma once
#include <string>
#include <vector>

#include "HyruleMath.h"
#include "HComponent.h"

namespace hyrule
{
	class HEntity;

	class HTransform : public HComponent
	{
	public:
		HTransform() = delete;
		HTransform(HEntity* _entity);
		~HTransform() override = default;

	private:
		Vector3D position;
		Quaternion rotation;
		Vector3D scale;

	private:
		hyrule::HTransform* parent;
		std::vector<HTransform*> children;

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
		HTransform* GetParent();
		void SetParent(HTransform*);
		void RemoveParent();

		void AddChild(HTransform*);
		void RemoveChild(HTransform*);

		HTransform* GetChild(const size_t _index);
		std::vector<HTransform*> Getchildren();
		size_t GetChildCount();
		HTransform* FindChild(const std::string&);
		HTransform* FindChild(const InstanceID&);

	public:
		virtual void OnDestroy() final;
	};
}

