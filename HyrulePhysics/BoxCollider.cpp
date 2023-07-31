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
		/// ������ ������ �� ����ϰ� ������
		/// ���̽� ������ �ĳ��� Ž���ϴ� ����̳�.
		/// ������ å�� ����Ǿ��ִ� ��Ŭ���̹� �˰����� �̿��ص� ������ ����.
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
			// ���⿡ �ִ� ���� �����ϰ� �ִ� ���� ã�ƾ���.
			// Matrix4x4 world = object->GetWorldTM();
			Matrix4x4 world = object->GetWorldTM();

			// std::map<float, Face> facesMap;

			auto faces = shape->GetFaces(world);
			float max{ FLT_MIN };
			Vector3D normal{};

			// ���̽��� Ž���ϸ鼭 ���⺤�Ͷ� ���̽��� �븻�� �ִ��� ������ ���� ã�´�.
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

				// ������ �ԽǷк��� �۴ٸ� ���� ����.
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

			// ������ ���� ����
			this->inertia.Ixx = inv12 * _mass * (h2 + d2);		// Ixx
			this->inertia.Iyy = inv12 * _mass * (w2 + d2);		// Iyy
			this->inertia.Izz = inv12 * _mass * (w2 + h2);		// Izz
			this->inertia.Ixy = 0.f;							// Ixy
			this->inertia.Iyz = 0.f;							// Iyz
			this->inertia.Ixz = 0.f;							// Ixz

			// �ټ��� ��Ī ����
			this->inertia.Iyx = inertia.Ixy;
			this->inertia.Izy = inertia.Iyz;
			this->inertia.Izx = inertia.Ixz;

			return inertia;
		}
	}
}