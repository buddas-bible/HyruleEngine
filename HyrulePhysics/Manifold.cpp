#include "Manifold.h"

#include "HyruleMath.h"

#include <vector>

namespace Hyrule
{
	Manifold::Manifold(const Collider*& _A, const Collider*& _B) noexcept
		: A(_A), B(_B), 
		normal{}, tangent{}, depth{}, 
		// contactPoints{},
		contactNormal{}
	{
		
	}

	bool Manifold::IsColliding()
	{
		return this->collided;
	}

	Vector3D Manifold::GetNormal() const noexcept
	{
		return this->normal;
	}

	void Manifold::SetNormal(const Vector3D& _normal) noexcept
	{
		this->normal = _normal;
	}

	Vector3D Manifold::GetTangent() const noexcept
	{
		return this->tangent;
	}

	void Manifold::SetTangent(const Vector3D& _tangent) noexcept
	{
		this->tangent = _tangent;
	}

	Vector3D Manifold::GetContactNormal() const noexcept
	{
		return this->contactNormal;
	}

	void Manifold::SetContactNormal(const Vector3D& _contactNormal) noexcept
	{
		this->contactNormal = _contactNormal;
	}

	float Manifold::GetDepth() const noexcept
	{
		return this->depth;
	}

	void Manifold::SetDepth(float _depth) noexcept
	{
		this->depth = _depth;
	}

	/// <summary>
	/// 일단 2D때 했던 GJK를 그대로 옮겨옴
	/// </summary>
	void Manifold::CheckCollision()
	{
		// 임의의 방향 벡터
		Vector3D directionVec = Vector3D(1.f, 0.f, 0.f);

		// 방향 벡터로부터 서포트 포인트를 구함
		std::vector<Vector3D> simplex;

		// 원점
		Vector3D origin(0.f, 0.f, 0.f);
		Vector3D temp;

		size_t count = 0;

		while (true)
		{
			switch (simplex.size())
			{
				case 0:
				{
					// 서포트 포인트 A를 구함
					// simplex.push_back(GetSupportPoint(A, B, directionVec));
					directionVec = -directionVec;
				}
				break;

				case 1:
				{
					// 서포트 포인트 B를 구함
					Vector3D OA = simplex[0].Normalized();
					Vector3D AO = -OA;
					// simplex.push_back(GetSupportPoint(A, B, directionVec));

					// 서포트 포인트 B가 원점 너머에 있지 않으면 충돌하지 않음
					Vector3D OB = simplex[1].Normalized();

					if (OB.Dot(AO) < 0)
					{
						collided = false;
						return;
					}
				}
				break;

				case 2:
				{
					// 원점을 향한 방향 벡터를 구하기 위해서 삼중곱을 함
					Vector3D AB = simplex[1] - simplex[0];
					Vector3D AO = -simplex[0];
					directionVec = AB.Cross(AO).Cross(AB).Normalized();

					// AB 위에 원점이 있을 경우
					if (directionVec == origin)
					{
						directionVec = Vector3D(-AB.y, AB.x, 0.f).Normalized();
					}

					// 서포트 포인트 C를 구함
					// simplex.push_back(GetSupportPoint(A, B, directionVec));

					// 서포트 포인트 C가 원점 너머에 있지 않으면 충돌하지 않음
					Vector3D OC = simplex[2].Normalized();

					if (OC.Dot(directionVec) <= 0)
					{
						collided = false;
						return;
					}
				}
				break;

				case 3:
				{
					// 점이 중복된다면 리턴
					if ((simplex[0] == simplex[2]) || (simplex[0] == simplex[1]) || (simplex[1] == simplex[2]))
					{
						collided = false;
						return;
					}

					Vector3D CA = simplex[0] - simplex[2];
					Vector3D CB = simplex[1] - simplex[2];
					Vector3D CO = -simplex[2].Normalized();

					Vector3D nBC = CA.Cross(CB).Cross(CB).Normalized();
					Vector3D nAC = CB.Cross(CA).Cross(CA).Normalized();

					// AB에서 원점을 향해서 점을 찾기 시작한 것이니
					// nBC, nAC를 원점과 내적해서 각도가 제대로 나오는가 판단
					if (nBC.Dot(CO) <= 0 && nAC.Dot(CO) <= 0)
					{
						// 심플렉스 내부에 원점이 존재함

						// 현재 심플렉스 정보를 저장함
						// m_Simplex = simplex;
						// 
						// EPA(A, B);
						// 
						// FindContactPoint(manifold.normalVector, A, B);
						// manifold.tangentVector = Cross(manifold.normalVector, Vector3::Up).Normalized();
						collided = true;
						return;
					}

					if (nBC.Dot(CO) > 0)
					{
						// BC 영역 안에 원점이 존재함.
						directionVec = nBC;

						temp = simplex[0];
						// 점 A 삭제 및 배열을 당김
						simplex.erase(simplex.begin() + 0);
						count++;
						break;
					}
					else if (nAC.Dot(CO) > 0)
					{
						// AC 영역 안에 원점이 존재함.
						directionVec = nAC;

						temp = simplex[1];
						// 점 B 삭제 및 배열을 당김
						simplex.erase(simplex.begin() + 1);
						count++;
						break;
					}
				}
				break;
			}
		}

		collided = false;
		return;
	}
}