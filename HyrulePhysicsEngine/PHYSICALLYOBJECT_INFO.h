#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Quaternion;

	namespace Physics
	{
		enum class ColliderType : int
		{
			SPHERE,
			BOX,
			CAPSULE,
			POLYHEDRON,
			MESH,
		};

		/// <summary>
		/// 트랜스폼 정보를 포인터로 받음
		/// 강체 시뮬레이션으로 인해 로컬 트랜스폼 정보가 변경될 수도 있으니 필요하다.
		/// 
		/// isChanged는 트랜스폼 정보가 변경 되었는지에 대한 bool값임.
		/// 트랜스폼 정보가 변경된다면 팔진 트리를 다시 탐색해야하기 때문에
		/// 정보를 주고받을 필요가 있다.
		/// </summary>
		struct TRANSFORM_INFO
		{
			Vector3D* pPosition;
			Quaternion* pRotation;
			Vector3D* pScale;
			bool* isChanged;
		};
		
		/// <summary>
		/// 콜라이더 타입 (구, 박스, 캡슐, 다면체, 메쉬)
		/// 
		/// 다면체, 메쉬만 배열과 인덱스 정보를 받음.
		/// </summary>
		struct COLLIDER_INFO
		{
			int colliderType;
			Vector3D* pPointArr;
			size_t pPointArrSize;
			size_t* pIndexArr;
			size_t pIndexArrSize;
		};
	}
}
