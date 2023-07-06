#pragma once
#include "IPhysics.h"

#include <string>
#include <vector>
#include <map>

#pragma comment(lib, "HyruleMath.lib")
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class RigidBody;
		class IRigidBody;
		class Collider;
		class ICollider;
		class Object;

		struct COLLIDER_INFO;
		struct TRANSFORM_INFO;

		class HyrulePhysics : public IPhysics
		{
		public:
			HyrulePhysics() noexcept = default;
			virtual ~HyrulePhysics() = default;

		public:
			virtual ICollider* AddCollider(const std::wstring& _name/*, TRANSFORM_INFO* _trnsinfo*/, COLLIDER_INFO* _colinfo) override;	// 오브젝트에 콜라이더를 추가함.
			virtual IRigidBody* AddRigidBody(const std::wstring&/*, TRANSFORM_INFO* _trnsinfo*/) override;	// 오브젝트에 강체를 추가함

			virtual void RemoveCollider(const std::wstring&, ICollider*) override;	// 콜라이더 포인터를 받아서 삭제
			virtual void RemoveCollider(const std::wstring&, int) override;			// 콜라이더 인덱스를 받아서 삭제
			virtual void RemoveRigidBody(const std::wstring&) override;				// 강체 삭제

		public:
			virtual long Initialize() override;
			virtual void CollisionDetection() override;									// 콜리전 체크
			virtual void CollisionResponse(float) override;							// 강체 시뮬레이션
			virtual void WorldReset() override;										// 월드에 있는 콜라이더와 강체를 모두 지움
			virtual void Finalize() override;

			virtual void SetWorldGravity(const Hyrule::Vector3D&) override;			// 월드 중력을 설정함.

		private:
			/// <summary>
			/// 오브젝트 매니저로 뺄 예정.
			/// </summary>
			std::map<std::wstring, Object*> objectMap;								// 오브젝트랑 이름, 포인터 맵
			std::vector<Object*> objectList;										// 단순 탐색하고 싶어서.

			Collider* CreateCollider(Object*, COLLIDER_INFO*);						// 콜라이더를 만듬
			RigidBody* CreateRigidBody(Object*);									// 강체를 만듬

			Hyrule::Vector3D gravity;

			bool useOctree{ true };
		};

		extern "C"
		{
			__declspec(dllexport) IPhysics* CreatePhysics();
		}
	}
}

/*
게임 엔진으로부터 물리를 분리하고 싶은데

게임 엔진의 강체 컴포넌트, 콜라이더 컴포넌트에 대해서 어떻게 해야하나..
게임 엔진에서 강체 컴포넌트가 추가되면 물리 엔진의 강체를 만들어서 반환 받게 하고...??


또한 디버깅만을 위한 UI를 만들어야 겠다.
물리 관련 디버깅 정보를 그래프로 표시를 한다든가.
충돌 이벤트가 발생한 위치에 무언가로 표시를 해둔다던가...
*/


/*
2023.07.03
정리해보자.

----목표----
- 외부(게임 엔진)에서 콜라이더와 강체를 추가하면 물리 엔진 내에서 충돌 감지 및 시뮬레이션을 하도록 하고 싶음. (DLL로 완전히 구분하고 싶음.)


----진행 하려는 것 정리----
- 콜라이더 나 강체를 물리 엔진에 추가할 때 해당 게임 오브젝트의 이름을 받아오려고 함.
- 게임 오브젝트의 이름을 받아서 물리 엔진 내에서 오브젝트가 생성된 적이 있었는지 체크를 함.
- 생성된 오브젝트가 없으면 만들어서 거기에 요청한 콜라이더 또는 강체를 추가함.
- 강체는 오브젝트당 1개만 생성될 수 있고, 한 오브젝트에 이미 강체가 붙어있다면 지우고 새로 할당함 (라이브러리를 사용하는 밖에서 시도를 못하도록 구분해야함)
- 강체는 이름만 받아서 문제 없이 추가 시킬 수 있지만, 해당 오브젝트에 콜라이더가 존재하지 않으면 물리 시뮬레이션 자체가 이뤄지지 않음.
- 물리 엔진 밖에서 Octree를 설정 하는 것도 추가해야할...듯?


----고민 중----
콜라이더
- 하나의 오브젝트에 복수의 콜라이더를 지원해줄 것인가?
- 그렇다면 강체도 그걸 다 인식하나?
- 텐서 계산을 어떻게 하나?

Shape
- 콜라이더를 추가할 때, Shape 정보를 전달 받아야하는데 이것을 어떻게 전달 받아야할지 고민임.
- 충돌 감지는 GJK로 할 예정인데, GJK는 Shape의 형태가 중요한 것이 아니라 점 구름 형태여도 충돌 감지가 가능하다! (볼록 다면체 한정)
- 하지만 강체 시뮬레이션을 위해서 관성 텐서를 계산한다든가. 정확한 충돌 지점을 알기 위해서는 Shape의 정보를 구체적인 정보를 알고 있으면 좋을 듯 싶다.
- 점 구름과 인덱스 정보를 받아오는걸 전제로 코드 짜야할지 고민이다.

트랜스폼
- 게임 엔진에서 게임 오브젝트의 트랜스폼 정보에 대해서도 고민 중이다.
- 콜라이더의 충돌 관련 불리언 값을 전달 받은 게임 엔진이 해당 게임 오브젝트와 그 부모의 이벤트 함수를 호출할 것이다. (아마도)
- 그것보다도 트랜스폼 부모 자식 관계.
- 충돌 감지할 때엔 월드 트랜스폼을 전달 받아서 충돌 감지를 하는 것까지 OK.
- 강체 시뮬레이션에서는 그로 인해 트랜스폼 정보가 변경되어야 하는데.
- 자신의 월드 트랜스폼, 부모의 월드 트랜스폼 둘 다 전달 받아서 충돌 이벤트 이후에 변경된 자신의 월드 트랜스폼 정보에 부모 월드 역행렬을 곱하는 것으로 본인의 로컬 트랜스폼 정보를 끌어 내야하나?
- 벌써부터 굉장히 번거로운 일이 될 것 같다.

- 월드 트랜스폼을 매 프래임 전달을 받아야하나?
- 참조로 받아 놓고 계속 쓰는 경우도 생각해봤지만, 옥트리 떄문에 고민 중이다.
- 매 프레임 옥트리를 지우고 다시 오브젝트 밀어놓고 노드 나누고 충돌 감지 하는 것 자체가 값이 좀 나갈거 같아서
- 이전 프레임에서 트랜스폼 정보가 바뀌었다는 것을 어떻게 전달 받아야하지?
- Set 함수를 하나 만들어놔서 게임 엔진쪽에서 트랜스폼의 Set함수를 호출하는 곳에서 불리언 값을 변경하게 놔둬야하나?
- 그러고 매 프레임 불리언 값 가진 오브젝트는 노드에서 지웠다가 다시 밀어넣고?

- 점점 내가 하려던 것으로부터 많이 멀어지고 있는 거 같다.
- 그냥 콜라이더랑 강체만 추가하고 알아서 연산해주는 무언가를 하고 싶었을 뿐인데
- 조금씩 게임 엔진으로부터 받아야하는 뭔가가 많아지는게 이게 맞나 싶다.
*/