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
			Vector3D* pPointArr;			// ���ؽ� �迭 ������
			size_t pPointArrSize;			// �迭 ����
			size_t* pIndexArr;				// �ε��� �迭 ������
			size_t pIndexArrSize;			// �ε��� ����
		};

		/// <summary>
		/// �ݶ��̴� Ÿ�� (��, �ڽ�, ĸ��, �ٸ�ü, ���, �޽�)
		/// 
		/// �ٸ�ü, �޽��� �迭�� �ε��� ������ ����.
		/// </summary>
		struct COLLIDER_INFO
		{
			std::string shapeName;
            std::string tag;
            void* userData;
			// size_t collisionType;						// Static, Dynamic
			SHAPE_INPO shapeInfo;
			Vector3D colliderSize{ 1.f, 1.f, 1.f };			// ���� x�� ���� ����
			Vector3D colliderCenter{ 0.f, 0.f ,0.f };
		};
	}
}
