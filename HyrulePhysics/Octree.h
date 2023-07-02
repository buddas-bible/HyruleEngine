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
		/// 물리 엔진에서 공간 분할만을 위한 팔진트리
		/// 재사용성은 신경쓰지도 않을 예정
		/// </summary>
		// template <typename Data, size_t DepthLimit>
		class Octree
		{
		public:

			/// <summary>
			/// 노드에 들어갈 데이터
			/// </summary>
			struct Data
			{
			public:
				// 콜라이더 중심으로부터 가장 먼 점과의 길이를 넘기자
				Data(Collider* _data, const Vector3D& _centre, float _length) :
					data(_data), 
					aabb(_centre, _length)
				{}
				~Data() {}

			public:
				bool operator== (const Collider* _rawData) noexcept
				{
					return data == _rawData;
				}

				Collider* data;				// 데이터
				AABB aabb;
			};

			/// <summary>
			/// 트리 노드
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
				const size_t depth;				// 현재 깊이
				AABB aabb;
				Node* child[8];					// 자식 노드
				std::vector<Data*> dataList;

			public:
				// 현재 노드의 데이터 개수
				size_t GetCount()
				{
					return dataList.size();
				}

				// 콜라이더 체크를 위해서 반환하는 것임.
				std::vector<Data*> GetDataList()
				{
					return dataList;
				}

				/// <summary>
				/// 노드에 데이터를 넣고 다음 노드를 생성할지 판단.
				/// </summary>
				void AddData(Node* _node, Data* _data, size_t _depth)
				{
					// AABB 다 체크하고 AddData를 호출하기 때문에
					// 가장 깊은 곳까지 도달하면 바로 배열에 넣는다.
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

						// 자식 노드의 AABB를 계산해서 데이터의 AABB와 충돌 하는지 체크
						if (AABB(tempCenter - tempHalfLength, tempCenter + tempHalfLength).CollidingAABB(_data->aabb))
						{
							// 충돌하면 노드를 생성함.
							child[i] = new Node(tempCenter - tempHalfLength, aabb.length * 0.5f, _depth - 1);

							// 해당 노드의 AddData를 호출함.
							child[i]->AddData(child[i], _data, _depth - 1);
						}
					}
				}

				/// <summary>
				/// 노드에 있는 데이터를 삭제함.
				/// </summary>
				void RemoveData(Data* _data)
				{
					// 현재 노드에서 데이터를 삭제
					auto a = dataList.erase(remove(dataList.begin(), dataList.end(), _data));
					
					// 없으면 자식 노드도 확인 안함.
					if (a == dataList.end())
					{
						return;
					}

					// for문으로 자식 노드에 데이터 삭제 함수를 호출
					// 재귀 돌면서 자식 노드의 데이터를 삭제
					for (auto& e : child)
					{
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
			Octree() noexcept = default;
			Octree(const Vector3D& _centre, float _length, size_t _limit = 4) : depthLimit(_limit), root()
			{
				root = new Node(_centre, _length, _limit);
			}
			~Octree() noexcept = default;

		private:
			const size_t depthLimit;
			Node* root;
		
		public:
			void Insert(Data* _data)
			{
				// root의 AABB와 Data의 AABB를 비교하고 공간 안에 있으면 넣음.
				root->AddData(root, _data, depthLimit);
			}

			void RemoveData(Data* _data)
			{
				root->RemoveData(_data);
				// root 노드에 데이터 삭제를 요청
				// root 노드는 반복문을 돌면서 자식 노드의 데이터 삭제 함수를 호출
				// 재귀로 자식 노드의 데이터 삭제를 호출함.
			}
		};
	}
}


/*
공간의 중심과 크기를 기본 설정값으로 받음
min, max 부피 데이터는 중심과 크기로 채워넣어질 예정 

데이터의 포인터와, 데이터의 중심과 크기를 받아서 데이터의 부피를 설정함

Insert를 하면 우선 
*/