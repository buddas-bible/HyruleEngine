#pragma once
#include <string>
#include <vector>

namespace Hyrule
{
	namespace Physics
	{
		class RigidBody;
		class Collider;
		class Transform;

		struct Object
		{
		public:
			Object() noexcept = delete;
			Object(const std::wstring&) noexcept;
			~Object() noexcept = default;

		public:
			std::wstring name;
			Transform* transform;
			
		public:
			RigidBody* rigidbody;
			std::vector<Collider*> colliders;
		};
	}
}

/*
오브젝트?
콜라이더? 강체? 이것들을 설정할 빌더를 만들어야 하는디...
이것들을 생성할 때 전달할 매개변수가 너무 많다.


게임 오브젝트 이름
로컬 트랜스폼 정보 (위치, 회전, 스케일)
월드 트랜스폼 정보
버텍스 정보
인덱스 정보
*/
