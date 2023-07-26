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
			Matrix4x4 colliderTM = ToTransformMatrix(center, Quaternion::Identity(), size);

			Matrix4x4 colliderWorld = colliderTM *= objectTM;
			colliderWorld.m[3] = {0.f, 0.f, 0.f, 1.f};
			Matrix4x4 invColliderWorld = colliderWorld.Inverse();

			float maxDist{ FLT_MIN };
			size_t index{ 0 };
			Vector3D dir{ (_direction * invColliderWorld).Normalized() };

			for (size_t i = 0; i < shape->GetPoints().size(); i++)
			{
				float dist{ shape->GetPoints()[i].Dot(dir) };

				if (dist > maxDist)
				{
					maxDist = dist;
					index = i;
				}
			}

			return shape->GetPoints()[index] * colliderTM;
		}

		Face BoxCollider::FindSupportFace(const Vector3D& _direction)
		{
			// ���⿡ �ִ� ���� �����ϰ� �ִ� ���� ã�ƾ���.
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
			std::vector<Face> same;

			for (auto& e : faces)
			{
				float radius{ 1.f - e.normal.Dot(normal) };
				// float error{ std::fabs(max - radius) };

				// ������ �ԽǷк��� �۴ٸ� ���� ����.
				if (radius <= Epsilon)
				{
					same.push_back(e);

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
	}
}