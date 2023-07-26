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

		Matrix3x3 BoxCollider::GetInertiaTensor(float _mass) noexcept
		{
			const auto& points{ shape->GetPoints(ToTransformMatrix(Vector3D(), object->GetRotation(), object->GetScale())) };
			const auto& index{ shape->GetIndies() };

			const float inv6 = (1.f / 6.f);
			const float inv24 = (1.f / 24.f);
			const float inv60 = (1.f / 60.f);
			const float inv120 = (1.f / 120.f);

			float intg[10] = {};

			for (size_t triangle = 0; triangle < index.size(); triangle += 3)
			{
				// �ﰢ�� ���� ������
				auto v0 = points[index[triangle]];
				auto v1 = points[index[triangle + 1]];
				auto v2 = points[index[triangle + 2]];

				// �ﰢ���� �� ����, ������ ����
				auto a = v1 - v0;
				auto b = v2 - v0;
				auto aCrossb = a.Cross(b);

				Vector3D f0, f1, f2;
				Vector3D g0, g1, g2;

				// �� ����
				Subexpressions(v0.x, v1.x, v2.x, f0.x, f1.x, f2.x, g0.x, g1.x, g2.x);
				Subexpressions(v0.y, v1.y, v2.y, f0.y, f1.y, f2.y, g0.y, g1.y, g2.y);
				Subexpressions(v0.z, v1.z, v2.z, f0.z, f1.z, f2.z, g0.z, g1.z, g2.z);

				// ������ ������� ������.
				intg[0] += aCrossb.x * f0.x;

				intg[1] += aCrossb.x * f1.x;
				intg[2] += aCrossb.y * f1.y;
				intg[3] += aCrossb.z * f1.z;

				intg[4] += aCrossb.x * f2.x;
				intg[5] += aCrossb.y * f2.y;
				intg[6] += aCrossb.z * f2.z;

				intg[7] += aCrossb.x * (v0.y * g0.x + v1.y * g1.x + v2.y * g2.x);
				intg[8] += aCrossb.y * (v0.z * g0.y + v1.z * g1.y + v2.z * g2.y);
				intg[9] += aCrossb.z * (v0.x * g0.z + v1.x * g1.z + v2.x * g2.z);
			}

			intg[0] *= inv6;

			intg[1] *= inv24;
			intg[2] *= inv24;
			intg[3] *= inv24;

			intg[4] *= inv60;
			intg[5] *= inv60;
			intg[6] *= inv60;

			intg[7] *= inv120;
			intg[8] *= inv120;
			intg[9] *= inv120;

			// ����
			// mass = intg[0];
			float mass = _mass;

			// ���� �߽�
			this->centerOfMass = { intg[1], intg[2], intg[3] };
			if (intg[0] != 0.f)
			{
				this->centerOfMass /= intg[0];
			}
			else
			{
				centerOfMass = { 0.f, 0.f, 0.f };
			}

			// ������ ���� ����
			this->inertia.Ixx = intg[5] + intg[6];		// Ixx
			this->inertia.Iyy = intg[4] + intg[6];		// Iyy
			this->inertia.Izz = intg[4] + intg[5];		// Izz
			this->inertia.Ixy = -intg[7];				// Ixy
			this->inertia.Iyz = -intg[8];				// Iyz
			this->inertia.Ixz = -intg[9];				// Ixz

			// ���� �߽ɿ� ���� ����
			this->inertia.Ixx -= mass * (centerOfMass.y * centerOfMass.y + centerOfMass.z * centerOfMass.z);
			this->inertia.Iyy -= mass * (centerOfMass.x * centerOfMass.x + centerOfMass.z * centerOfMass.z);
			this->inertia.Izz -= mass * (centerOfMass.x * centerOfMass.x + centerOfMass.y * centerOfMass.y);

			this->inertia.Ixy += mass * centerOfMass.x * centerOfMass.y;
			this->inertia.Iyz += mass * centerOfMass.y * centerOfMass.z;
			this->inertia.Ixz += mass * centerOfMass.y * centerOfMass.z;

			// �ټ��� ��Ī ����
			this->inertia.Iyx = inertia.Ixy;
			this->inertia.Izy = inertia.Iyz;
			this->inertia.Izx = inertia.Ixz;

			return inertia;
		}
	}
}