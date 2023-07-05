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
		/// Ʈ������ ������ �����ͷ� ����
		/// ��ü �ùķ��̼����� ���� ���� Ʈ������ ������ ����� ���� ������ �ʿ��ϴ�.
		/// 
		/// isChanged�� Ʈ������ ������ ���� �Ǿ������� ���� bool����.
		/// Ʈ������ ������ ����ȴٸ� ���� Ʈ���� �ٽ� Ž���ؾ��ϱ� ������
		/// ������ �ְ���� �ʿ䰡 �ִ�.
		/// </summary>
		struct TRANSFORM_INFO
		{
			Vector3D* pPosition;
			Quaternion* pRotation;
			Vector3D* pScale;
			bool* isChanged;
		};
		
		/// <summary>
		/// �ݶ��̴� Ÿ�� (��, �ڽ�, ĸ��, �ٸ�ü, �޽�)
		/// 
		/// �ٸ�ü, �޽��� �迭�� �ε��� ������ ����.
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
