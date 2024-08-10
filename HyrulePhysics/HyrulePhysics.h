#pragma once
#include "../HyrulePhysicsEngine/IPhysics.h"

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>

#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class IRigidBody;
		class RigidBody;

		class ICollider;
		class Collider;
		
		class Object;
		class Simplex;

		struct COLLIDER_INFO;
		struct RaycastInfo;

		class HyrulePhysics : public IPhysics
		{
		public:
			HyrulePhysics() noexcept = default;
			virtual ~HyrulePhysics() = default;

		public:
			virtual ICollider* CreateCollider(const std::string&, COLLIDER_INFO*) override;	// ������Ʈ�� �ݶ��̴��� �߰���.
			virtual IRigidBody* CreateRigidBody(const std::string&) override;					// ������Ʈ�� ��ü�� �߰���

		public:
			virtual long Initialize() override;
			virtual void CollisionDetection() override;										// �ݸ��� üũ
			virtual void CollisionResponse(float) override;									// ��ü �ùķ��̼�
			virtual void ApplyObjectDestroy() override;
			virtual void Finalize() override;

            virtual bool Raycast(const Vector3D&, const Vector3D&, RaycastInfo*) override;
            virtual bool Raycast(const Vector3D&, const Vector3D&, const float, RaycastInfo*) override;

			virtual void SetWorldGravity(const Hyrule::Vector3D&) override;					// ���� �߷��� ������.

		private:
			std::set<std::pair<Collider*, Collider*>> colliderTable;
			std::vector<Manifold> manifoldArray;

			Hyrule::Vector3D gravity;

			bool useOctree{ true };
		};

        __declspec(dllexport) IPhysics* CreatePhysics();
	}
}

/*
���� �������κ��� ������ �и��ϰ� ������

���� ������ ��ü ������Ʈ, �ݶ��̴� ������Ʈ�� ���ؼ� ��� �ؾ��ϳ�..
���� �������� ��ü ������Ʈ�� �߰��Ǹ� ���� ������ ��ü�� ���� ��ȯ �ް� �ϰ�...??


���� ����븸�� ���� UI�� ������ �ڴ�.
���� ���� ����� ������ �׷����� ǥ�ø� �Ѵٵ簡.
�浹 �̺�Ʈ�� �߻��� ��ġ�� ���𰡷� ǥ�ø� �صдٴ���...
*/


/*
2023.07.03
�����غ���.

----��ǥ----
- �ܺ�(���� ����)���� �ݶ��̴��� ��ü�� �߰��ϸ� ���� ���� ������ �浹 ���� �� �ùķ��̼��� �ϵ��� �ϰ� ����. (DLL�� ������ �����ϰ� ����.)


----���� �Ϸ��� �� ����----
- �ݶ��̴� �� ��ü�� ���� ������ �߰��� �� �ش� ���� ������Ʈ�� �̸��� �޾ƿ����� ��.
- ���� ������Ʈ�� �̸��� �޾Ƽ� ���� ���� ������ ������Ʈ�� ������ ���� �־����� üũ�� ��.
- ������ ������Ʈ�� ������ ���� �ű⿡ ��û�� �ݶ��̴� �Ǵ� ��ü�� �߰���.
- ��ü�� ������Ʈ�� 1���� ������ �� �ְ�, �� ������Ʈ�� �̹� ��ü�� �پ��ִٸ� ����� ���� �Ҵ��� (���̺귯���� ����ϴ� �ۿ��� �õ��� ���ϵ��� �����ؾ���)
- ��ü�� �̸��� �޾Ƽ� ���� ���� �߰� ��ų �� ������, �ش� ������Ʈ�� �ݶ��̴��� �������� ������ ���� �ùķ��̼� ��ü�� �̷����� ����.
- ���� ���� �ۿ��� Octree�� ���� �ϴ� �͵� �߰��ؾ���...��?


----��� ��----
�ݶ��̴�
- �ϳ��� ������Ʈ�� ������ �ݶ��̴��� �������� ���ΰ�?
- �׷��ٸ� ��ü�� �װ� �� �ν��ϳ�?
- �ټ� ����� ��� �ϳ�?

Shape
- �ݶ��̴��� �߰��� ��, Shape ������ ���� �޾ƾ��ϴµ� �̰��� ��� ���� �޾ƾ����� �����.
- �浹 ������ GJK�� �� �����ε�, GJK�� Shape�� ���°� �߿��� ���� �ƴ϶� �� ���� ���¿��� �浹 ������ �����ϴ�! (���� �ٸ�ü ����)
- ������ ��ü �ùķ��̼��� ���ؼ� ���� �ټ��� ����Ѵٵ簡. ��Ȯ�� �浹 ������ �˱� ���ؼ��� Shape�� ������ ��ü���� ������ �˰� ������ ���� �� �ʹ�.
- �� ������ �ε��� ������ �޾ƿ��°� ������ �ڵ� ¥������ ����̴�.

Ʈ������
- ���� �������� ���� ������Ʈ�� Ʈ������ ������ ���ؼ��� ��� ���̴�.
- �ݶ��̴��� �浹 ���� �Ҹ��� ���� ���� ���� ���� ������ �ش� ���� ������Ʈ�� �� �θ��� �̺�Ʈ �Լ��� ȣ���� ���̴�. (�Ƹ���)
- �װͺ��ٵ� Ʈ������ �θ� �ڽ� ����.
- �浹 ������ ���� ���� Ʈ�������� ���� �޾Ƽ� �浹 ������ �ϴ� �ͱ��� OK.
- ��ü �ùķ��̼ǿ����� �׷� ���� Ʈ������ ������ ����Ǿ�� �ϴµ�.
- �ڽ��� ���� Ʈ������, �θ��� ���� Ʈ������ �� �� ���� �޾Ƽ� �浹 �̺�Ʈ ���Ŀ� ����� �ڽ��� ���� Ʈ������ ������ �θ� ���� ������� ���ϴ� ������ ������ ���� Ʈ������ ������ ���� �����ϳ�?
- ������� ������ ���ŷο� ���� �� �� ����.

- ���� Ʈ�������� �� ������ ������ �޾ƾ��ϳ�?
- ������ �޾� ���� ��� ���� ��쵵 �����غ�����, ��Ʈ�� ������ ��� ���̴�.
- �� ������ ��Ʈ���� ����� �ٽ� ������Ʈ �о���� ��� ������ �浹 ���� �ϴ� �� ��ü�� ���� �� ������ ���Ƽ�
- ���� �����ӿ��� Ʈ������ ������ �ٲ���ٴ� ���� ��� ���� �޾ƾ�����?
- Set �Լ��� �ϳ� �������� ���� �����ʿ��� Ʈ�������� Set�Լ��� ȣ���ϴ� ������ �Ҹ��� ���� �����ϰ� ���־��ϳ�?
- �׷��� �� ������ �Ҹ��� �� ���� ������Ʈ�� ��忡�� �����ٰ� �ٽ� �о�ְ�?

- ���� ���� �Ϸ��� �����κ��� ���� �־����� �ִ� �� ����.
- �׳� �ݶ��̴��� ��ü�� �߰��ϰ� �˾Ƽ� �������ִ� ���𰡸� �ϰ� �;��� ���ε�
- ���ݾ� ���� �������κ��� �޾ƾ��ϴ� ������ �������°� �̰� �³� �ʹ�.
*/