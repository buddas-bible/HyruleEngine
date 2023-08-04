#pragma once
#include <vector>
#include <map>
#include "AABB.h"

#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		class Collider;
		class AABB;

		template<typename DataType>
		struct Data
		{
			DataType data{};
			AABB boundingVolum;
		};

		template<typename DataType>
		struct OctreeNode
		{
			OctreeNode<DataType>* parent{};				// 
			OctreeNode<DataType>* children[8]{};			// 자식 포인터
			AABB boundingVolum;					// 경계 볼륨
			std::vector<Data<DataType>> data;		// 현재 노드가 가지고 있는 데이터
			
			int Count();						// 현재 노드가 가진 데이터 개수
			bool isLeaf();
		};

		template<typename DataType>
		int OctreeNode<DataType>::Count()
		{
			int count{};
			for (auto& child : children)
			{
				count += child->Count();
			}

			return count + data.size();
		}

		template<typename DataType>
		bool OctreeNode<DataType>::isLeaf()
		{
			// 흠.. 리프 조건을 어떻게 할까
			return children;
		}

		// ============================================================================================= //

		template<typename DataType>
		class Octree_v2
		{
		private:
			OctreeNode<DataType>* root;
			std::map<DataType, OctreeNode<DataType>*> treeData;

		public:
			int	Count();													// 트리에 삽입된 데이터 개수
			void Insert(DataType _data);									// 데이터를 삽입함
			void Remove(DataType _data);									// 데이터를 삭제함
			void Clear();

			std::vector<DataType> Query(const AABB& _AABB);				// AABB와 충돌 가능성이 있는 데이터를 모아서 반환함
			std::vector<DataType> Query(const Vector3D& _point);			// 점과 충돌 가능성이 있는 데이터를 모아서 반환함
			
			void Raycast(const Vector3D& _from, const Vector3D& _to);		// 레이와 충돌한 데이터를 찾음

		private:
			void Insert(Data&, OctreeNode<DataType>*);
			void Clear(OctreeNode<DataType>*);
			AABB GetChildVolum(int, const AABB&);
			void Query(const AABB&, OctreeNode<DataType>*, std::vector<DataType>&);
			void Query(const Vector3D&, OctreeNode<DataType>*, std::vector<DataType>&);
		};

		/// <summary>
		/// 트리에 있는 데이터 개수
		/// </summary>
		template<typename DataType>
		int Octree_v2<DataType>::Count()
		{
			return root->Count();
		}

		/// <summary>
		/// 트리에 데이터를 삽입
		/// </summary>
		template<typename DataType>
		void Octree_v2<DataType>::Insert(DataType _data)
		{
			// root의 children에 완전 포함되는지 판단
			// 
			// 완전 포함되지 않는다면 현재 노드에 넣음
			// 완전 포함된다면 그 자식 노드도 비교함
			// 당연히 리프 노드면 그냥 넣음.
			Data data;
			data.data = _data;
			data.boundingVolum = _data->GetAABB();
			Insert(data, root);
		}

		template<typename DataType>
		void Octree_v2<DataType>::Insert(Data<DataType>& _data, OctreeNode<DataType>* _node)
		{
			if (_node->isLeaf())
			{
				// 리프 노드라면 데이터를 넣음.
				_node->data.push_back(_data.data);
				treeData.insert(std::make_pair(_data.data, _node));
			}
			else
			{
				// 리프 노드가 아니라면
				for (auto i = 0; i < 8; i++)
				{
					AABB child = GetChildVolum(i, _node->boundingVolum);

					// 데이터가 자식 노드에게 완전히 포함된다면
					if (child.Contains(_data.boundingVolum))
					{
						if (_node->children[i] == nullptr)
						{
							_node->children[i] = new OctreeNode<DataType>;
							_node->children[i]->parent = _node;
							_node->children[i]->boundingVolum = child;
						}

						// 완전 포함되는 노드가 있다면 자식 노드를 재귀적으로 탐색한다.
						Insert(_data, _node->children[i]);
						return;
					}
				}

				// 자식 순회가 다 끝났는데 함수가 안끝났으면 현재 노드에 데이터를 넣음
				_node->data.push_back(_data.data);
				treeData.insert(std::make_pair(_data.data, _node));
			}
		}

		/// <summary>
		/// 트리에서 데이터를 삭제
		/// </summary>
		template<typename DataType>
		void Octree_v2<DataType>::Remove(DataType _data)
		{
			auto itr = treeData.find(_data);
			if (itr == treeData.end())
			{
				// 데이터가 트리에 없음
				return;
			}
			
			auto data = (*itr).first;
			auto node = (*itr).second;

			// 데이터를 트리에서 삭제함
			remove(node->data.begin(), node->data.end(), data);
			treeData.erase(itr);

			// 노드에 남은 데이터가 없으면 공간을 분할할 필요가 없음
			if (node->Count() == 0)
			{
				Clear(node);
			}
		}

		/// <summary>
		/// 트리를 비움
		/// </summary>
		template<typename DataType>
		void Octree_v2<DataType>::Clear()
		{
			// 트리를 비운다.
			Clear(root);
			delete root;
			root = nullptr;
		}

		template<typename DataType>
		void Octree_v2<DataType>::Clear(OctreeNode<DataType>* _node)
		{
			if (_node->isLeaf())
			{
				// 리프는 자식을 가지고 있지 않음
				return;
			}

			for (auto& child : _node->children)
			{
				if (child)
				{
					Clear(child);
					delete child;
					child = nullptr;
				}
			}
		}

		template<typename DataType>
		AABB Octree_v2<DataType>::GetChildVolum(int _index, const AABB& _parentVolum)
		{
			Vector3D center = _parentVolum.center;
			Vector3D extents = (_parentVolum.max - _parentVolum.min) * 0.25f;

			if (_index & 1)
			{
				center.x += extents.x;
			}
			else
			{
				center.x -= extents.x;
			}

			if (_index & 2)
			{
				center.z += extents.z;
			}
			else
			{
				center.z -= extents.z;
			}

			if (_index & 4)
			{
				center.y += extents.y;
			}
			else
			{
				center.y -= extents.y;
			}

			AABB result;
			result.min = center - extents;
			result.max = center + extents;

			return result;
		}

		/// <summary>
		/// 조건에 맞는 데이터를 모두 가져옴
		/// </summary>
		template<typename DataType>
		std::vector<Collider*> Octree_v2<DataType>::Query(const AABB& _AABB)
		{
			std::vector<Collider*> result;

			Query(_AABB, root, result);

			return result;
		}

		template<typename DataType>
		std::vector<Collider*> Octree_v2<DataType>::Query(const Vector3D& _point)
		{
			std::vector<Collider*> result;

			Query(_point, root, result);

			return result;
		}

		template<typename DataType>
		void Octree_v2<DataType>::Query(const AABB& _AABB, OctreeNode<DataType>* _node, std::vector<DataType*>& _list)
		{
			for (auto& d : _node->data)
			{
				// 노드가 가지고 있는 데이터들과 비교함
				if (d->GetAABB().Overlap(_AABB))
				{
					// 충돌 가능성이 있는 데이터를 반환함
					_list.push_back(d);
				}
			}

			for (auto child : _node->children)
			{
				// 노드의 자식에 완전 포함되는지 비교함
				if (child->boundingVolum.Contains(_AABB))
				{
					Query(_AABB, child, _list);
					return;
				}
			}
		}

		template<typename DataType>
		void Octree_v2<DataType>::Query(const Vector3D& _point, OctreeNode<DataType>* _node, std::vector<DataType*>& _list)
		{
			for (auto& d : _node->data)
			{
				// 노드가 가지고 있는 데이터들과 비교함
				if (d->GetAABB().ContainsPoint(_point))
				{
					// 충돌 가능성이 있는 데이터를 반환함
					_list.push_back(d);
				}
			}

			for (auto child : _node->children)
			{
				// 노드의 자식에 완전 포함되는지 비교함
				if (child->boundingVolum.ContainsPoint(_point))
				{
					Query(_point, child, _list);
					return;
				}
			}
		}
	}
}

