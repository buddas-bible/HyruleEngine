#include "BoxCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Shape.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		BoxCollider::BoxCollider(Object* _obj, COLLIDER_INFO* _info) noexcept : 
			Collider(_obj),
			shape(Shapes::boxShape)
		{
			_obj->colliders.push_back(this);
			this->SetSize(_info->colliderSize);
			this->SetCenter(_info->colliderCenter);
		}

		/// <summary>
		/// 지금은 깡으로 다 계산하고 있지만
		/// 페이스 단위로 쳐내고 탐색하는 방식이나.
		/// 오렌지 책에 설명되어있는 힐클라이밍 알고리즘을 이용해도 좋을거 같다.
		/// </summary>
		Vector3D BoxCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Matrix4x4 objectTM = object->GetWorldTM();

			Matrix4x4 colliderWorld = objectTM;
			colliderWorld.m[3] = {0.f, 0.f, 0.f, 1.f};
			Matrix4x4 invColliderWorld = colliderWorld.Inverse();

			size_t index{ 0 };
			float maxDist{ (shape->GetPoints()[index] * objectTM).Dot(_direction) };
			// Vector3D dir{ (_direction * invColliderWorld).Normalized() };

			for (size_t i = 1; i < shape->GetPoints().size(); i++)
			{
				float dist{ (shape->GetPoints()[i] * objectTM).Dot(_direction) };

				if (dist >= maxDist)
				{
					maxDist = dist;
					index = i;
				}
			}

			return shape->GetPoints()[index] * objectTM;
		}

		Face BoxCollider::FindSupportFace(const Vector3D& _direction)
		{
			// 방향에 있는 점을 포함하고 있는 면을 찾아야함.
			// Matrix4x4 world = object->GetWorldTM();
			Matrix4x4 world = object->GetWorldTM();

			// std::map<float, Face> facesMap;

			auto faces = shape->GetFaces(world);
			float max{ FLT_MIN };
			Vector3D normal{};

			// 페이스를 탐색하면서 방향벡터랑 페이스의 노말과 최대한 평행한 것을 찾는다.
			for (auto& e : faces)
			{
				float radius{ e.normal.Dot(_direction) };

				if (radius > max)
				{
					max = radius;
					normal = e.normal;
				}
			}

			std::vector<Edge> edges;
			// std::vector<Face> same;

			for (auto& e : faces)
			{
				float radius{ 1.f - e.normal.Dot(normal) };
				// float error{ std::fabs(max - radius) };

				// 오차가 입실론보다 작다면 같은 면임.
				if (radius <= 0.01f)
				{
					// same.push_back(e);

					for (auto& edge : e.edge)
					{
						auto itr = std::find(edges.begin(), edges.end(), edge);

						if (itr != edges.end())
						{
							edges.erase(itr);
						}
						else
						{
							edges.push_back(edge);
						}
					}
				}
			}

			return Face(edges);
		}

		Matrix3x3 BoxCollider::GetInertiaTensor(float _mass) noexcept
		{
			Vector3D scl{ object->GetScale() };
			const float width{ 1.f * scl.x };
			const float height{ 1.f * scl.y };
			const float depth{ 1.f * scl.z };

			const float w2{ width * width };
			const float h2{ height * height };
			const float d2{ depth * depth };

			const float inv12{ 1.f / 12.f };

			// 원점에 대한 관성
			this->inertia.Ixx = inv12 * _mass * (h2 + d2);		// Ixx
			this->inertia.Iyy = inv12 * _mass * (w2 + d2);		// Iyy
			this->inertia.Izz = inv12 * _mass * (w2 + h2);		// Izz
			this->inertia.Ixy = 0.f;							// Ixy
			this->inertia.Iyz = 0.f;							// Iyz
			this->inertia.Ixz = 0.f;							// Ixz

			// 텐서는 대칭 형태
			this->inertia.Iyx = inertia.Ixy;
			this->inertia.Izy = inertia.Iyz;
			this->inertia.Izx = inertia.Ixz;

			return inertia;
		}
	}
}