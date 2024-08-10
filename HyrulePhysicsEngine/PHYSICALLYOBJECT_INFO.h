#pragma once
#include <string>
#include "../HyruleMath/HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;
	struct Quaternion;

	namespace Physics
	{
		enum SHAPE_TYPE : size_t
		{
			SPHERE		= 0,
			BOX			= 10,
			CAPSULE		= 20,
			CONVEX		= 30,
			PLANE		= 40,
			MESH		= 50,
		};
		
		struct SHAPE_INPO
		{
			size_t shapeType;
			Vector3D* pPointArr;			// 버텍스 배열 포인터
			size_t pPointArrSize;			// 배열 개수
			size_t* pIndexArr;				// 인덱스 배열 포인터
			size_t pIndexArrSize;			// 인덱스 개수
		};

		/// <summary>
		/// 콜라이더 타입 (구, 박스, 캡슐, 다면체, 평면, 메쉬)
		/// 
		/// 다면체, 메쉬만 배열과 인덱스 정보를 받음.
		/// </summary>
		struct COLLIDER_INFO
		{
			std::string shapeName;
            std::string tag;
            void* userData;
			// size_t collisionType;						// Static, Dynamic
			SHAPE_INPO shapeInfo;
			Vector3D colliderSize{ 1.f, 1.f, 1.f };			// 구는 x만 영향 받음
			Vector3D colliderCenter{ 0.f, 0.f ,0.f };
		};
	}
}
