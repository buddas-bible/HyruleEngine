#pragma once
#include <vector>
#include <list>

#include "Vector3D.h"
#include "AABB.h"


// template <typename Type>
// class has_Length
// {
// 	template <typename T>
// 	static float Length(decltype(&T::ㅍGetLength));
// 
// 	template <typename T>
// 	static char Length();
// ㅍ
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
		/// 물리 엔진에서 공간 분할만을 위한 팔진트리
		/// 재사용성은 신경쓰지도 않을 예정
		/// </summary>
		template <typename DataType>
		class Octree
		{
		public:
			/// <summary>
			/// 트리 노드
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
				const size_t depth;				// 현재 깊이
				AABB aabb;
				Node* children[8];				// 자식 노드
				std::list<DataType> dataList;

			public:
				// 현재 노드의 데이터 개수
				size_t GetCount()
				{
					return dataList.size();
				}

				// 콜라이더 체크를 위해서 반환하는 것임.
				void GetDataList(std::vector<std::list<DataType>>& _container)
				{
					if (depth == 0)
					{
						_container.push_back(dataList);
						return;
					}

					// 노드에 데이터 개수가 2개 이하면 패스
					if (dataList.size() < 2)
					{
						return;
					}

					// 노드에 데이터 개수가 6개 이상이면 자식 탐색
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
				/// 노드에 데이터를 넣고 다음 노드를 생성할지 판단.
				/// </summary>
				void AddData(Node* _node, DataType _data, size_t _depth)
				{
					// AABB 다 체크하고 AddData를 호출하기 때문에
					// 가장 깊은 곳까지 도달하면 바로 배열에 넣는다.
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

						// 자식 노드의 AABB를 계산해서 데이터의 AABB와 충돌 하는지 체크
						if (childBoundingBox.Overlap(dataBoundingBox))
						{
							// 충돌하면 노드를 생성함.
							if (children[i] == nullptr)
							{
								children[i] = new Node(tempCenter, aabb.length / 2, _depth - 1);
							}

							// 해당 노드의 AddData를 호출함.
							children[i]->AddData(children[i], _data, _depth - 1);
						}
					}
				}

				/// <summary>
				/// 노드에 있는 데이터를 삭제함.
				/// </summary>
				void RemoveData(DataType _data)
				{
					// 현재 노드에서 데이터를 삭제
					auto itr = std::find(dataList.begin(), dataList.end(), _data);

					// 없으면 자식 노드도 확인 안함.
					if (itr == dataList.end())
					{
						return;
					}

					dataList.erase(itr);

					// for문으로 자식 노드에 데이터 삭제 함수를 호출
					// 재귀 돌면서 자식 노드의 데이터를 삭제
					for (auto& e : children)
					{
						if (e == nullptr)
							continue;
						e->RemoveData(_data);
					}
				}

				/// <summary>
				/// 자식 노드의 센터와 한 변의 길이를 구함.
				/// 
				/// 자식 노드를 만들기 전에 먼저 체크하고 싶어서 그러함.
				/// </summary>
				void GetChildCenter(size_t _id, Vector3D& _outCenter, Vector3D& _outLength)
				{
					Vector3D center = aabb.center;
					Vector3D length = Vector3D(aabb.length, aabb.length, aabb.length) * 0.25f;

					// 3차원 배열로 생각하고
					// 비트 연산으로
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
				// root의 AABB와 Data의 AABB를 비교하고 공간 안에 있으면 넣음.
				root->AddData(root, _data, DepthLimit);
			}

			void Remove(const DataType& _data)
			{
				root->RemoveData(_data);
				// root 노드에 데이터 삭제를 요청
				// root 노드는 반복문을 돌면서 자식 노드의 데이터 삭제 함수를 호출
				// 재귀로 자식 노드의 데이터 삭제를 호출함.
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