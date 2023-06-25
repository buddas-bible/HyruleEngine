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
	/// �ϴ� 2D�� �ߴ� GJK�� �״�� �Űܿ�
	/// </summary>
	void Manifold::CheckCollision()
	{
		// ������ ���� ����
		Vector3D directionVec = Vector3D(1.f, 0.f, 0.f);

		// ���� ���ͷκ��� ����Ʈ ����Ʈ�� ����
		std::vector<Vector3D> simplex;

		// ����
		Vector3D origin(0.f, 0.f, 0.f);
		Vector3D temp;

		size_t count = 0;

		while (true)
		{
			switch (simplex.size())
			{
				case 0:
				{
					// ����Ʈ ����Ʈ A�� ����
					// simplex.push_back(GetSupportPoint(A, B, directionVec));
					directionVec = -directionVec;
				}
				break;

				case 1:
				{
					// ����Ʈ ����Ʈ B�� ����
					Vector3D OA = simplex[0].Normalized();
					Vector3D AO = -OA;
					// simplex.push_back(GetSupportPoint(A, B, directionVec));

					// ����Ʈ ����Ʈ B�� ���� �ʸӿ� ���� ������ �浹���� ����
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
					// ������ ���� ���� ���͸� ���ϱ� ���ؼ� ���߰��� ��
					Vector3D AB = simplex[1] - simplex[0];
					Vector3D AO = -simplex[0];
					directionVec = AB.Cross(AO).Cross(AB).Normalized();

					// AB ���� ������ ���� ���
					if (directionVec == origin)
					{
						directionVec = Vector3D(-AB.y, AB.x, 0.f).Normalized();
					}

					// ����Ʈ ����Ʈ C�� ����
					// simplex.push_back(GetSupportPoint(A, B, directionVec));

					// ����Ʈ ����Ʈ C�� ���� �ʸӿ� ���� ������ �浹���� ����
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
					// ���� �ߺ��ȴٸ� ����
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

					// AB���� ������ ���ؼ� ���� ã�� ������ ���̴�
					// nBC, nAC�� ������ �����ؼ� ������ ����� �����°� �Ǵ�
					if (nBC.Dot(CO) <= 0 && nAC.Dot(CO) <= 0)
					{
						// ���÷��� ���ο� ������ ������

						// ���� ���÷��� ������ ������
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
						// BC ���� �ȿ� ������ ������.
						directionVec = nBC;

						temp = simplex[0];
						// �� A ���� �� �迭�� ���
						simplex.erase(simplex.begin() + 0);
						count++;
						break;
					}
					else if (nAC.Dot(CO) > 0)
					{
						// AC ���� �ȿ� ������ ������.
						directionVec = nAC;

						temp = simplex[1];
						// �� B ���� �� �迭�� ���
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