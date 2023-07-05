#pragma once
#include "Component.h"

#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;
	class Transform;

	class Camera : public Component
	{
	public:
		Camera() noexcept = delete;
		Camera(GameObject*) noexcept;
		~Camera() noexcept = default;

		enum class CameraView : int
		{
			PERSPECTIVE = 0,
			ORTHOGRAPHIC = 1,
		};

	private:
		CameraView mode;

		Vector3D up;
		Vector3D look;
		Vector3D right;

		Matrix4x4 viewTM;
		Matrix4x4 persProjTM;
		Matrix4x4 orthProjTM;

		float angle;
		float ratio;

		float height;
		float width;
		float near;
		float far;

	public:
		Matrix4x4 GetViewTM() const noexcept;
		Matrix4x4 GetProjTM() const noexcept;
		Matrix4x4 GetViewProjTM() const noexcept;

		void CreateViewTM() noexcept;

		void CameraLookAtLH(const Vector3D&, const Vector3D&, const Vector3D&);
		void CameraLookToLH(const Vector3D&, const Vector3D&, const Vector3D&);
		void CameraPerspectiveFovLH(float, float, float, float);
		void CameraOrthographicLH(float, float, float, float);
		void MoveX(float);
		void MoveY(float);
		void MoveZ(float);

		void MoveRight(float);
		void MoveUp(float);
		void MoveForward(float);

		void Pitch(float);
		void Yaw(float);
		void Roll(float);

		void SetCameraView(CameraView);

	private:

	public:
		virtual void Awake() override;
		virtual void Start() override;
		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LastUpdate() override;
		virtual void Render() override;

		// 		virtual void OnTriggerEnter(Collider*) abstract;
		// 		virtual void OnTriggerStay(Collider*) abstract;
		// 		virtual void OnTriggerExit(Collider*) abstract;
		// 
		// 		virtual void OnTriggerEnter() abstract;
		// 		virtual void OnTriggerStay() abstract;
		// 		virtual void OnTriggerExit() abstract;

		virtual void OnCollisionEnter(Collider*) override;
		virtual void OnCollisionStay(Collider*) override;
		virtual void OnCollisionExit(Collider*) override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override;
		virtual void OnCollisionExit() override;

		virtual void OnEnable() override;
		virtual void OnDestroy() override;
	};
}

