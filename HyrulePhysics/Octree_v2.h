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
			OctreeNode<DataType>* children[8]{};			// �ڽ� ������
			AABB boundingVolum;					// ��� ����
			std::vector<Data<DataType>> data;		// ���� ��尡 ������ �ִ� ������
			
			int Count();						// ���� ��尡 ���� ������ ����
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
			// ��.. ���� ������ ��� �ұ�
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
			int	Count();													// Ʈ���� ���Ե� ������ ����
			void Insert(DataType _data);									// �����͸� ������
			void Remove(DataType _data);									// �����͸� ������
			void Clear();

			std::vector<DataType> Query(const AABB& _AABB);				// AABB�� �浹 ���ɼ��� �ִ� �����͸� ��Ƽ� ��ȯ��
			std::vector<DataType> Query(const Vector3D& _point);			// ���� �浹 ���ɼ��� �ִ� �����͸� ��Ƽ� ��ȯ��
			
			void Raycast(const Vector3D& _from, const Vector3D& _to);		// ���̿� �浹�� �����͸� ã��

		private:
			void Insert(Data&, OctreeNode<DataType>*);
			void Clear(OctreeNode<DataType>*);
			AABB GetChildVolum(int, const AABB&);
			void Query(const AABB&, OctreeNode<DataType>*, std::vector<DataType>&);
			void Query(const Vector3D&, OctreeNode<DataType>*, std::vector<DataType>&);
		};

		/// <summary>
		/// Ʈ���� �ִ� ������ ����
		/// </summary>
		template<typename DataType>
		int Octree_v2<DataType>::Count()
		{
			return root->Count();
		}

		/// <summary>
		/// Ʈ���� �����͸� ����
		/// </summary>
		template<typename DataType>
		void Octree_v2<DataType>::Insert(DataType _data)
		{
			// root�� children�� ���� ���ԵǴ��� �Ǵ�
			// 
			// ���� ���Ե��� �ʴ´ٸ� ���� ��忡 ����
			// ���� ���Եȴٸ� �� �ڽ� ��嵵 ����
			// �翬�� ���� ���� �׳� ����.
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
				// ���� ����� �����͸� ����.
				_node->data.push_back(_data.data);
				treeData.insert(std::make_pair(_data.data, _node));
			}
			else
			{
				// ���� ��尡 �ƴ϶��
				for (auto i = 0; i < 8; i++)
				{
					AABB child = GetChildVolum(i, _node->boundingVolum);

					// �����Ͱ� �ڽ� ��忡�� ������ ���Եȴٸ�
					if (child.Contains(_data.boundingVolum))
					{
						if (_node->children[i] == nullptr)
						{
							_node->children[i] = new OctreeNode<DataType>;
							_node->children[i]->parent = _node;
							_node->children[i]->boundingVolum = child;
						}

						// ���� ���ԵǴ� ��尡 �ִٸ� �ڽ� ��带 ��������� Ž���Ѵ�.
						Insert(_data, _node->children[i]);
						return;
					}
				}

				// �ڽ� ��ȸ�� �� �����µ� �Լ��� �ȳ������� ���� ��忡 �����͸� ����
				_node->data.push_back(_data.data);
				treeData.insert(std::make_pair(_data.data, _node));
			}
		}

		/// <summary>
		/// Ʈ������ �����͸� ����
		/// </summary>
		template<typename DataType>
		void Octree_v2<DataType>::Remove(DataType _data)
		{
			auto itr = treeData.find(_data);
			if (itr == treeData.end())
			{
				// �����Ͱ� Ʈ���� ����
				return;
			}
			
			auto data = (*itr).first;
			auto node = (*itr).second;

			// �����͸� Ʈ������ ������
			remove(node->data.begin(), node->data.end(), data);
			treeData.erase(itr);

			// ��忡 ���� �����Ͱ� ������ ������ ������ �ʿ䰡 ����
			if (node->Count() == 0)
			{
				Clear(node);
			}
		}

		/// <summary>
		/// Ʈ���� ���
		/// </summary>
		template<typename DataType>
		void Octree_v2<DataType>::Clear()
		{
			// Ʈ���� ����.
			Clear(root);
			delete root;
			root = nullptr;
		}

		template<typename DataType>
		void Octree_v2<DataType>::Clear(OctreeNode<DataType>* _node)
		{
			if (_node->isLeaf())
			{
				// ������ �ڽ��� ������ ���� ����
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
		/// ���ǿ� �´� �����͸� ��� ������
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
				// ��尡 ������ �ִ� �����͵�� ����
				if (d->GetAABB().Overlap(_AABB))
				{
					// �浹 ���ɼ��� �ִ� �����͸� ��ȯ��
					_list.push_back(d);
				}
			}

			for (auto child : _node->children)
			{
				// ����� �ڽĿ� ���� ���ԵǴ��� ����
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
				// ��尡 ������ �ִ� �����͵�� ����
				if (d->GetAABB().ContainsPoint(_point))
				{
					// �浹 ���ɼ��� �ִ� �����͸� ��ȯ��
					_list.push_back(d);
				}
			}

			for (auto child : _node->children)
			{
				// ����� �ڽĿ� ���� ���ԵǴ��� ����
				if (child->boundingVolum.ContainsPoint(_point))
				{
					Query(_point, child, _list);
					return;
				}
			}
		}
	}
}
