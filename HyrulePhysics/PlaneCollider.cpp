#include "PlaneCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"

#include "AABB.h"

namespace Hyrule
{
    namespace Physics
    {
        PlaneCollider::PlaneCollider(Object* _obj, COLLIDER_INFO* _info) noexcept :
            Collider(_obj),
            shape(Shapes::planeShape)
        {
            _obj->colliders.push_back(this);
            this->SetSize(_info->colliderSize);
            this->SetCenter(_info->colliderCenter);
        }

        Vector3D PlaneCollider::GetPosition()
        {
            return center * object->GetWorldTM();
        }

        Quaternion PlaneCollider::GetRotation()
        {
            return object->GetRotation();
        }

        Vector3D PlaneCollider::GetScale()
        {
            Vector3D scl{ object->GetScale() };

            return Vector3D(scl.x * size.x, scl.y * size.y, scl.z * size.z);
        }

        float PlaneCollider::GetLength()
        {
            return (GetScale() * 0.5f).Length();
        }

        Matrix4x4 PlaneCollider::GetLocalTM()
        {
            return ToTransformMatrix(center, Quaternion::Identity(), size);
        }

        Matrix4x4 PlaneCollider::GetWorldTM()
        {
            return GetLocalTM() * object->GetWorldTM();
        }

        Vector3D PlaneCollider::GetSize()
        {
            return size;
        }

        Vector3D PlaneCollider::GetCenter()
        {
            return center;
        }

        AABB PlaneCollider::GetAABB()
        {
            Matrix4x4 objectTM = GetWorldTM();

            Vector3D p = shape->GetPoints()[0] * objectTM;

            Vector3D Min = p;
            Vector3D Max = p;

            for (size_t i = 1; i < shape->GetPoints().size(); i++)
            {
                auto e = shape->GetPoints()[1] * objectTM;

                e.x = std::min(Min.x, e.x);
                e.y = std::min(Min.y, e.y);
                e.z = std::min(Min.z, e.z);

                e.x = std::max(Max.x, e.x);
                e.y = std::max(Max.y, e.y);
                e.z = std::max(Max.z, e.z);
            }

            return AABB(Min, Max);
        }

        Vector3D PlaneCollider::FindFarthestPoint(const Vector3D& _direction)
        {
            Matrix4x4 world = GetWorldTM();
            Matrix4x4 colliderWorld = world;
            colliderWorld.m[3] = { 0.f, 0.f, 0.f, 1.f };
            Matrix4x4 invColliderWorld = colliderWorld.Inverse();

            size_t index{ 0 };
            Vector3D dir{ (_direction * invColliderWorld).Normalized() };
            float maxDist{ (shape->GetPoints()[index]).Dot(dir) };

            for (size_t i = 1; i < shape->GetPoints().size(); i++)
            {
                float dist{ (shape->GetPoints()[i]).Dot(dir) };

                if (dist >= maxDist)
                {
                    maxDist = dist;
                    index = i;
                }
            }

            return shape->GetPoints()[index] * colliderWorld;
        }

        Face PlaneCollider::FindSupportFace(const Vector3D&)
        {
            return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
        }

        Matrix3x3 PlaneCollider::GetInertiaTensor(float _mass) noexcept
        {
            // 			const auto& points{ shape->GetPoints(ToTransformMatrix(Vector3D(), object->GetRotation(), object->GetScale())) };
            // 			const auto& index{ shape->GetIndies() };
            // 
            // 			const float inv6 = 1 / 6;
            // 			const float inv24 = 1 / 24;
            // 			const float inv60 = 1 / 60;
            // 			const float inv120 = 1 / 120;
            // 
            // 			float intg[10] = {};
            // 
            // 			for (size_t triangle = 0; triangle < index.size(); triangle += 3)
            // 			{
            // 				// 삼각형 점을 가져옴
            // 				auto v0 = points[triangle];
            // 				auto v1 = points[triangle + 1];
            // 				auto v2 = points[triangle + 2];
            // 
            // 				// 삼각형의 변 벡터, 외적을 구함
            // 				auto a = v1 - v0;
            // 				auto b = v2 - v0;
            // 				auto aCrossb = a.Cross(b);
            // 
            // 				Vector3D f0, f1, f2;
            // 				Vector3D g0, g1, g2;
            // 
            // 				// 면 적분
            // 				Subexpressions(v0.x, v1.x, v2.x, f0.x, f1.x, f2.x, g0.x, g1.x, g2.x);
            // 				Subexpressions(v0.y, v1.y, v2.y, f0.y, f1.y, f2.y, g0.y, g1.y, g2.y);
            // 				Subexpressions(v0.z, v1.z, v2.z, f0.z, f1.z, f2.z, g0.z, g1.z, g2.z);
            // 
            // 				// 적분한 결과값을 저장함.
            // 				intg[0] += aCrossb.x * f0.x;
            // 
            // 				intg[1] += aCrossb.x * f1.x;
            // 				intg[2] += aCrossb.y * f1.y;
            // 				intg[3] += aCrossb.z * f1.z;
            // 
            // 				intg[4] += aCrossb.x * f2.x;
            // 				intg[5] += aCrossb.y * f2.y;
            // 				intg[6] += aCrossb.z * f2.z;
            // 
            // 				intg[7] += aCrossb.x * (v0.y * g0.x + v1.y * g1.x + v2.y * g2.x);
            // 				intg[8] += aCrossb.y * (v0.z * g0.y + v1.z * g1.y + v2.z * g2.y);
            // 				intg[9] += aCrossb.z * (v0.x * g0.z + v1.x * g1.z + v2.x * g2.z);
            // 			}
            // 
            // 			intg[0] *= inv6;
            // 
            // 			intg[1] *= inv24;
            // 			intg[2] *= inv24;
            // 			intg[3] *= inv24;
            // 
            // 			intg[4] *= inv60;
            // 			intg[5] *= inv60;
            // 			intg[6] *= inv60;
            // 
            // 			intg[7] *= inv120;
            // 			intg[8] *= inv120;
            // 			intg[9] *= inv120;
            // 
            // 			// 질량
            // 			float mass = _mass;
            // 			// mass = intg[0];
            // 
            // 			// 질량 중심
            // 			this->centerOfMass = { intg[1], intg[2], intg[3] };
            // 			this->centerOfMass /= intg[0];
            // 
            // 			// 원점에 대한 관성
            // 			this->inertia.Ixx = intg[5] + intg[6];		// Ixx
            // 			this->inertia.Iyy = intg[4] + intg[6];		// Iyy
            // 			this->inertia.Izz = intg[4] + intg[5];		// Izz
            // 			this->inertia.Ixy = -intg[7];				// Ixy
            // 			this->inertia.Iyz = -intg[8];				// Iyz
            // 			this->inertia.Ixz = -intg[9];				// Ixz
            // 
            // 			// 질량 중심에 대한 관성
            // 			this->inertia.Ixx -= mass * (centerOfMass.y * centerOfMass.y + centerOfMass.z * centerOfMass.z);
            // 			this->inertia.Iyy -= mass * (centerOfMass.x * centerOfMass.x + centerOfMass.z * centerOfMass.z);
            // 			this->inertia.Izz -= mass * (centerOfMass.x * centerOfMass.x + centerOfMass.y * centerOfMass.y);
            // 
            // 			this->inertia.Ixy += mass * centerOfMass.x * centerOfMass.y;
            // 			this->inertia.Iyz += mass * centerOfMass.y * centerOfMass.z;
            // 			this->inertia.Ixz += mass * centerOfMass.y * centerOfMass.z;
            // 
            // 			// 텐서는 대칭 형태
            // 			this->inertia.Iyx = inertia.Ixy;
            // 			this->inertia.Izy = inertia.Iyz;
            // 			this->inertia.Izx = inertia.Ixz;

            return inertia;
        }

        size_t PlaneCollider::GetType() noexcept
        {
            return shape->GetType();
        }
    }
}