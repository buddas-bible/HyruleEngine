#pragma once
#include <vector>

#include "Vector3D.h"
#include "AABB.h"


namespace Hyrule
{
	class Collider;


	namespace Physics
	{
		/// <summary>
		/// ���� �������� ���� ���Ҹ��� ���� ����Ʈ��
		/// ���뼺�� �Ű澲���� ���� ����
		/// </summary>
		template <typename DataType, size_t DepthLimit = 4>
		class Octree
		{
		public:

			/// <summary>
			/// ��忡 �� ������
			/// </summary>
			struct Data
			{
			public:
				// �ݶ��̴� �߽����κ��� ���� �� ������ ���̸� �ѱ���
				Data(DataType* _data, const Vector3D& _centre, float _length) :
					data(_data), 
					aabb(_centre, _length)
				{}
				~Data() {}

			public:
				bool operator== (const DataType* _rawData) noexcept
				{
					return data == _rawData;
				}

				DataType* data;				// ������
				AABB aabb;
			};

			/// <summary>
			/// Ʈ�� ���
			/// </summary>
			struct Node
			{
			public:
				Node() noexcept = delete;
				Node(const Vector3D& _centre, float _length, size_t _depth) :
					aabb(_centre, _length),
					depth(_depth), child(), dataList()
				{}
				~Node() noexcept {}

			private:
				const size_t depth;				// ���� ����
				AABB aabb;
				Node* child[8];					// �ڽ� ���
				std::vector<Data*> dataList;

			public:
				// ���� ����� ������ ����
				size_t GetCount()
				{
					return dataList.size();
				}

				// �ݶ��̴� üũ�� ���ؼ� ��ȯ�ϴ� ����.
				void GetDataList()
				{
					// ��忡 ������ ������ 2�� ���ϸ� �н�
					if (dataList.size() < 2)
					{
						return;
					}

					// ��忡 ������ ������ 6�� �̻��̸� �ڽ� Ž��
					if (dataList.size() > 5)
					{
						for (auto& e : child)
						{
							e->GetDataList();
						}
					}
					else
					{
						Ž���ؾ��Ҹ���嵥����.push_back(dataList);
						return;
					}
				}

				/// <summary>
				/// ��忡 �����͸� �ְ� ���� ��带 �������� �Ǵ�.
				/// </summary>
				void AddData(Node* _node, Data* _data, size_t _depth)
				{
					// AABB �� üũ�ϰ� AddData�� ȣ���ϱ� ������
					// ���� ���� ������ �����ϸ� �ٷ� �迭�� �ִ´�.
					dataList.push_back(_data);

					if (depth == 0)
					{
						return;
					}

					for (size_t i = 0; i < 8; ++i)
					{
						Vector3D tempCenter;
						Vector3D tempHalfLength;

						this->GetChildCenter(i, tempCenter, tempHalfLength);

						// �ڽ� ����� AABB�� ����ؼ� �������� AABB�� �浹 �ϴ��� üũ
						if (AABB(tempCenter - tempHalfLength, tempCenter + tempHalfLength).CollidingAABB(_data->aabb))
						{
							// �浹�ϸ� ��带 ������.
							child[i] = new Node(tempCenter - tempHalfLength, aabb.length * 0.5f, _depth - 1);

							// �ش� ����� AddData�� ȣ����.
							child[i]->AddData(child[i], _data, _depth - 1);
						}
					}
				}

				/// <summary>
				/// ��忡 �ִ� �����͸� ������.
				/// </summary>
				void RemoveData(Data* _data)
				{
					// ���� ��忡�� �����͸� ����
					auto itr = dataList.erase(remove(dataList.begin(), dataList.end(), _data));
					
					// ������ �ڽ� ��嵵 Ȯ�� ����.
					if (itr == dataList.end())
					{
						return;
					}

					// for������ �ڽ� ��忡 ������ ���� �Լ��� ȣ��
					// ��� ���鼭 �ڽ� ����� �����͸� ����
					for (auto& e : child)
					{
						e->RemoveData(_data);
					}
				}

				/// <summary>
				/// �ڽ� ����� ���Ϳ� �� ���� ���̸� ����.
				/// 
				/// �ڽ� ��带 ����� ���� ���� üũ�ϰ� �; �׷���.
				/// </summary>
				void GetChildCenter(size_t _id, Vector3D& _outCenter, Vector3D& _outLength)
				{
					Vector3D center = aabb.center;
					Vector3D length = Vector3D(aabb.length, aabb.length, aabb.length) * 0.25f;

					// 3���� �迭�� �����ϰ�
					// ��Ʈ ��������
					if (_id & 1)
					{
						length.x *= -1.f;
					}
					if (_id & 2)
					{
						length.z *= -1.f;
					}
					if (_id & 4)
					{
						length.y *= -1.f;
					}

					_outCenter = center - length;
					_outLength = length;
				}
			};


		public:
			Octree() noexcept = default;
			Octree(const Vector3D& _centre, float _length) : root()
			{
				root = new Node(_centre, _length, DepthLimit);
			}
			~Octree() noexcept = default;

		private:
			// const size_t DepthLimit;
			Node* root{};
			
			std::vector<std::vector<Data*>> Ž���ؾ��Ҹ���嵥����;

		public:
			void Insert(Data* _data)
			{
				// root�� AABB�� Data�� AABB�� ���ϰ� ���� �ȿ� ������ ����.
				root->AddData(root, _data, DepthLimit);
			}

			void Remove(Data* _data)
			{
				root->RemoveData(_data);
				// root ��忡 ������ ������ ��û
				// root ���� �ݺ����� ���鼭 �ڽ� ����� ������ ���� �Լ��� ȣ��
				// ��ͷ� �ڽ� ����� ������ ������ ȣ����.
			}

			std::vector<std::vector<Data*>> GetDataList()
			{
				root->GetDataList();

				return Ž���ؾ��Ҹ���嵥����;
			}
		};
	}
}