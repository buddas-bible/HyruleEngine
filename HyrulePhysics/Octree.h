#pragma once
#include <vector>
#include <list>

#include "Vector3D.h"
#include "AABB.h"


// template <typename Type>
// class has_Length
// {
// 	template <typename T>
// 	static float Length(decltype(&T::��GetLength));
// 
// 	template <typename T>
// 	static char Length();
// ��
// public:
// 	enum
// 	{
// 		value = sizeof(Length<Type>(0) == sizeof(float))
// 	};
// };
// 
// template <typename Type>
// class has_Position
// {
// 	template <typename T>
// 	static hyrule::Vector3D Position(decltype(&T::GetPosition));
// 	
// 	template <typename T>
// 	static hyrule::Vector3D Position();
// 
// public:
// 	enum
// 	{
// 		value = sizeof(Position<Type>(0) == sizeof(float))
// 	};
// };

namespace hyrule
{
	class Collider;

	namespace Physics
	{

		/// <summary>
		/// ���� �������� ���� ���Ҹ��� ���� ����Ʈ��
		/// ���뼺�� �Ű澲���� ���� ����
		/// </summary>
		template <typename DataType>
		class Octree
		{
		public:
			/// <summary>
			/// Ʈ�� ���
			/// </summary>
			struct Node
			{
			public:
				Node() = delete;
				Node(const Vector3D& _centre, float _length, size_t _depth) :
					aabb(_centre, _length),
					depth(_depth), children(), dataList()
				{}
				~Node()
				{
					for (auto& child : children)
					{
						if (child != nullptr)
						{
							delete child;
							child = nullptr;
						}
					}
				}

			private:
				const size_t depth;				// ���� ����
				AABB aabb;
				Node* children[8];				// �ڽ� ���
				std::list<DataType> dataList;

			public:
				// ���� ����� ������ ����
				size_t GetCount()
				{
					return dataList.size();
				}

				// �ݶ��̴� üũ�� ���ؼ� ��ȯ�ϴ� ����.
				void GetDataList(std::vector<std::list<DataType>>& _container)
				{
					if (depth == 0)
					{
						_container.push_back(dataList);
						return;
					}

					// ��忡 ������ ������ 2�� ���ϸ� �н�
					if (dataList.size() < 2)
					{
						return;
					}

					// ��忡 ������ ������ 6�� �̻��̸� �ڽ� Ž��
					if (dataList.size() > 5)
					{
						for (auto& e : children)
						{
							if (e == nullptr)
							{
								continue;
							}

							e->GetDataList(_container);
						}
					}
					else
					{
						_container.push_back(dataList);
						return;
					}
				}

				/// <summary>
				/// ��忡 �����͸� �ְ� ���� ��带 �������� �Ǵ�.
				/// </summary>
				void AddData(Node* _node, DataType _data, size_t _depth)
				{
					// AABB �� üũ�ϰ� AddData�� ȣ���ϱ� ������
					// ���� ���� ������ �����ϸ� �ٷ� �迭�� �ִ´�.
					dataList.push_back(_data);

					if (depth == 0)
					{
						return;
					}

					Vector3D pos{ _data->GetPosition() };
					float length{ _data->GetLength() * 2.f };

					AABB dataBoundingBox{ pos, length };

					for (size_t i = 0; i < 8; ++i)
					{
						Vector3D tempCenter;
						Vector3D tempHalfLength;

						this->GetChildCenter(i, tempCenter, tempHalfLength);

						AABB childBoundingBox{ tempCenter, aabb.length / 2 };

						// �ڽ� ����� AABB�� ����ؼ� �������� AABB�� �浹 �ϴ��� üũ
						if (childBoundingBox.Overlap(dataBoundingBox))
						{
							// �浹�ϸ� ��带 ������.
							if (children[i] == nullptr)
							{
								children[i] = new Node(tempCenter, aabb.length / 2, _depth - 1);
							}

							// �ش� ����� AddData�� ȣ����.
							children[i]->AddData(children[i], _data, _depth - 1);
						}
					}
				}

				/// <summary>
				/// ��忡 �ִ� �����͸� ������.
				/// </summary>
				void RemoveData(DataType _data)
				{
					// ���� ��忡�� �����͸� ����
					auto itr = std::find(dataList.begin(), dataList.end(), _data);

					// ������ �ڽ� ��嵵 Ȯ�� ����.
					if (itr == dataList.end())
					{
						return;
					}

					dataList.erase(itr);

					// for������ �ڽ� ��忡 ������ ���� �Լ��� ȣ��
					// ��� ���鼭 �ڽ� ����� �����͸� ����
					for (auto& e : children)
					{
						if (e == nullptr)
							continue;
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
			Octree() = default;
			Octree(const Vector3D& _centre, float _length, size_t depth = 10) : root(), DepthLimit(6)
			{
				root = new Node(_centre, _length, DepthLimit);
			}
			~Octree()
			{
				if (root != nullptr)
				{
					delete root;
					root = nullptr;
				}
			}

		private:
			const size_t DepthLimit;
			Node* root;
			
		public:
			std::vector<std::list<DataType>> searchDataContainer;

		public:
			void Insert(const DataType& _data)
			{
				// root�� AABB�� Data�� AABB�� ���ϰ� ���� �ȿ� ������ ����.
				root->AddData(root, _data, DepthLimit);
			}

			void Remove(const DataType& _data)
			{
				root->RemoveData(_data);
				// root ��忡 ������ ������ ��û
				// root ���� �ݺ����� ���鼭 �ڽ� ����� ������ ���� �Լ��� ȣ��
				// ��ͷ� �ڽ� ����� ������ ������ ȣ����.
			}

			std::vector<std::list<DataType>>& GetDataList()
			{
				root->GetDataList(searchDataContainer);

				return searchDataContainer;
			}

			void DataListClear()
			{
				for (auto e : searchDataContainer)
				{
					e.clear();
				}
				searchDataContainer.clear();
			}
		};
	}
}